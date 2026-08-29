#include <string>
#include <fstream> /* ifstream */
#include <sstream> /* stringstream */
#include <chrono>
#include <print>
#include <functional>
#include <string_view>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

#include "File/File.h"
#include "Match/Engine.h"
#include "Match/BoyerMoore.h"

namespace fs = boost::filesystem;
namespace chrono = std::chrono;

TEST(BM, delta1) {
  std::string patrn = "badbacbacba";
  BoyerMoore bm(patrn);
  auto delta1 = bm.GetDelta1();
  std::array<int, UCHAR_MAX> expected;
  expected.fill(bm.GetPatrnSz());
  expected['a'] = 0;
  expected['b'] = 1;
  expected['c'] = 2;
  expected['d'] = 8;
  ASSERT_EQ(delta1, expected);
}

TEST(BoyerMooreTest, delta2) {
  std::string patrn = "badbacbacba";
  BoyerMoore bm(patrn);
  auto delta2 = bm.GetDelta2();
  /*
   * Table from Knuth, Donald; Morris, James H.; Pratt, Vaughan (1977).
   * "Fast pattern matching in strings".
   *
   * j          = 1  2  3  4  5  6  7  8  9  10  11
   * pattern[j] = b  a  d  b  a  c  b  a  c  b   a
   * f[j]       = 10 11 6  7  8  9  10 11 11 11  12
   * dd[j]      = 19 18 17 16 15 8  7  6  5  4   1
   * dd'[j]     = 19 18 17 16 15 8  13 12 8  12  1
   */
  std::vector<int> expected = {19, 18, 17, 16, 15, 8, 13, 12, 8, 12, 1};
  ASSERT_EQ(delta2, expected);
}

TEST(BM, Match) {
  std::string patrn = "bar";
  std::string text = "foobarfoobar";
  std::string text_startsw_bar = "bartenderbartenderbartender";
  BoyerMoore bm(patrn);
  auto line_match = bm.Match(text);

  std::cout << *line_match;
 
  line_match = bm.Match(text_startsw_bar);
  std::cout << *line_match;

  line_match = bm.Match(patrn);
  std::cout << *line_match;
}

class BMPerf :
    public testing::TestWithParam<std::string_view> {
};

TEST_P(BMPerf, BenchmarkAndCorrectness)
{
  std::string text;
  std::stringstream sstream;
  std::string patrn = std::string(BMPerf::GetParam());
  std::println("patrn (param) {}", patrn);

  BoyerMoore bm(patrn);
  fs::path path = "test/A_Pale_View_of_Hills.txt";
  File _file(path);
  std::ifstream& file = _file.GetStream();
  chrono::time_point<chrono::system_clock> start;
  chrono::time_point<chrono::system_clock> end;

  sstream << file.rdbuf();
  text = sstream.str();
  std::println("text length {}", text.length());

  /* string::find */
  std::vector<size_t> find_pos;
  start = chrono::system_clock::now();
  size_t pos = text.find(patrn, 0);
  while (pos != std::string::npos) {
    find_pos.push_back(pos);
    pos = text.find(patrn, pos + 1);
  }
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> find_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("string::find time: {}", find_time);

  /* Boyer-Moore */
  start = chrono::system_clock::now();
  auto bm_res = bm.Match(text);
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> bm_time = end - start;
  std::println("Boyer-Moore time: {}", bm_time);
  ASSERT_EQ(bm_res->GetMatPos(), find_pos);
  std::println("result: {}", bm_res->GetMatPos());

  /* std::boyer_moore_searcher */
  std::vector<size_t> std_bm_pos;
  std::boyer_moore_searcher bms(patrn.begin(), patrn.end());
  start = chrono::system_clock::now();
  auto bm_it = std::search(text.begin(), text.end(), bms);
  while (bm_it != text.end()) {
    std_bm_pos.push_back(bm_it - text.begin());
    bm_it = std::search(bm_it + 1, text.end(), bms);
  }
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> std_bms_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("std::boyer_moore_searcher time: {}", find_time);
  ASSERT_EQ(std_bm_pos, find_pos);

  /* re2 */
  std::vector<size_t> regex_engine_pos;
  auto engine = Engine(patrn);
  pos = 0;
  size_t text_sz = text.size();
  std::string_view sv(text);
  start = chrono::system_clock::now();
  while ((pos = engine.Find(sv, pos, text_sz)) != Engine::NOT_FOUND) {
    std::println("found at position {}", pos);
    regex_engine_pos.push_back(pos);
    pos += 1;
  }
  std::println("re2 time: {}", find_time);
  ASSERT_EQ(regex_engine_pos, find_pos);
}

INSTANTIATE_TEST_SUITE_P(Patterns, BMPerf,
  testing::Values(
    "Sachiko", /* frequent */
    "We were to become friends that summer and for a short time at least I was to be admitted into her confidence", /* long */
    "anxious",
    "A Pale View of Hills",
    "Ishiguro"
  ));
