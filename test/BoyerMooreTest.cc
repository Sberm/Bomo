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
  expected.fill(-1);
  expected['a'] = 10;
  expected['b'] = 9;
  expected['c'] = 8;
  expected['d'] = 2;
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
  std::string text = "foobarfoobar";
  std::string text_startsw_bar = "xbabaaabartenderbartenderbartender";
  std::string patrn = "bar";
  BoyerMoore bm(patrn);
  std::string_view capture;

  ASSERT_TRUE(bm.FindAndConsume(text, 0, text.size(), &capture));
  std::println("{} at {}", capture, capture.data() - text.data());
 
  ASSERT_TRUE(bm.FindAndConsume(text_startsw_bar, 0, text_startsw_bar.size(), &capture));
  std::println("{} at {}", capture, capture.data() - text_startsw_bar.data());

  ASSERT_TRUE(bm.FindAndConsume(patrn, 0, patrn.size(), &capture));
  std::println("{} at {}", capture, capture.data() - patrn.data());
}

class BMPerf : public testing::TestWithParam<std::string_view> {
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
    find_pos.emplace_back(pos);
    pos = text.find(patrn, pos + 1);
  }
  end = chrono::system_clock::now();

  chrono::duration<long, std::micro> find_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("string::find time: {}", find_time);


  /* Boyer-Moore */
  std::string_view capture;
  std::vector<size_t> bm_res;
  size_t start_pos = 0;
  size_t end_pos = text.size();

  start = chrono::system_clock::now();
  while (bm.FindAndConsume(text, start_pos, end_pos, &capture)) {
    bm_res.emplace_back(capture.data() - text.data());
    start_pos = capture.data() - text.data() + capture.size();
  }
  end = chrono::system_clock::now();

  chrono::duration<long, std::micro> bm_time = end - start;
  std::println("Boyer-Moore time: {}", bm_time);
  ASSERT_EQ(bm_res, find_pos);


  /* std::boyer_moore_searcher */
  std::vector<size_t> std_bm_pos;
  std::boyer_moore_searcher bms(patrn.begin(), patrn.end());

  start = chrono::system_clock::now();
  auto bm_it = std::search(text.begin(), text.end(), bms);
  while (bm_it != text.end()) {
    std_bm_pos.emplace_back(bm_it - text.begin());
    bm_it = std::search(bm_it + 1, text.end(), bms);
  }
  end = chrono::system_clock::now();

  chrono::duration<long, std::micro> std_bms_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("std::boyer_moore_searcher time: {}", find_time);
  ASSERT_EQ(std_bm_pos, find_pos);


  /* re2 */
  std::vector<size_t> regex_engine_pos;
  auto engine = Engine(patrn);
  std::string_view sv(text);
  std::vector<std::pair<size_t, size_t>> match_ranges;

  start = chrono::system_clock::now();
  engine.MatchStrAll(sv, match_ranges);
  end = chrono::system_clock::now();

  for (auto& match_range: match_ranges) {
    regex_engine_pos.emplace_back(match_range.first);
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
  )
);
