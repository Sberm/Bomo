#include <string>
#include <fstream> /* ifstream */
#include <sstream> /* stringstream */
#include <chrono>
#include <print>
#include <functional>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

#include "File/File.h"
#include "Match/BoyerMoore.h"

namespace fs = boost::filesystem;
namespace chrono = std::chrono;

TEST(BoyerMooreTest, boyer_moore_delta1) {
  std::string patrn = "badbacbacba";
  BoyerMoore bm(patrn);
  auto delta1 = bm.get_delta1();
  std::array<int, UCHAR_MAX> expected;
  expected.fill(bm.get_patrn_sz());
  expected['a'] = 0;
  expected['b'] = 1;
  expected['c'] = 2;
  expected['d'] = 8;
  ASSERT_EQ(delta1, expected);
}

TEST(BoyerMooreTest, boyer_moore_delta2) {
  std::string patrn = "badbacbacba";
  BoyerMoore bm(patrn);
  auto delta2 = bm.get_delta2();
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

TEST(BoyerMooreTest, match) {
  std::string patrn = "bar";
  std::string text = "foobarfoobar";
  std::string text_startsw_bar = "bartenderbartenderbartender";
  BoyerMoore bm(patrn);
  auto line_match = bm.match(text);

  std::cout << *line_match;
 
  line_match = bm.match(text_startsw_bar);
  std::cout << *line_match;

  line_match = bm.match(patrn);
  std::cout << *line_match;
}

TEST(BoyerMoorePerf, bomo_vs_find) {
  std::string text;
  std::stringstream sstream;

  // frequent
  // std::string patrn = "Sachiko";

  // long
  std::string patrn = "We were to become friends that summer and for a short time at least I was to be admitted into her confidence. I am not sure now how it was we first met. I remember one afternoon spotting her figure ahead of me on the path leading out of the housing precinct. I was hurrying, but Sachiko walked on with a steady stride. By that point we must have already known each other by name, for I remember calling to her as I got nearer.";

  // misc
  // std::string patrn = "anxious";
  // std::string patrn = "A Pale View of Hills";
  // std::string patrn = "Ishiguro";

  BoyerMoore bm(patrn);
  fs::path path = "test/A_Pale_View_of_Hills.txt";
  File _file(path);
  std::ifstream& file = _file.getStream();
  chrono::time_point<chrono::system_clock> start;
  chrono::time_point<chrono::system_clock> end;
  std::vector<size_t> find_pos;
  std::vector<size_t> std_bm_pos;
  std::boyer_moore_searcher bms(patrn.begin(), patrn.end());

  sstream << file.rdbuf();
  text = sstream.str();
  std::println("text length {}", text.length());
  
  // Boyer-Moore
  start = chrono::system_clock::now();
  auto bm_res = bm.match(text);
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> bm_time = end - start;
  std::println("Boyer-Moore time: {}", bm_time);

  // string::find
  start = chrono::system_clock::now();
  size_t pos = text.find(patrn, 0);
  while (pos != std::string::npos) {
    find_pos.push_back(pos);
    pos = text.find(patrn, pos + 1);
  }
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> find_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("string::find time: {}", find_time);

  // std::boyer_moore_searcher
  start = chrono::system_clock::now();
  auto bm_it = std::search(text.begin(), text.end(), bms);
  while (bm_it != text.end()) {
    std_bm_pos.push_back(bm_it - text.begin());
    bm_it = std::search(bm_it + 1, text.end(), bms);
  }
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> std_bms_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("std::boyer_moore_searcher time: {}", find_time);

  // re2
  start = chrono::system_clock::now();
  auto bm_it = std::search(text.begin(), text.end(), bms);
  while (bm_it != text.end()) {
    std_bm_pos.push_back(bm_it - text.begin());
    bm_it = std::search(bm_it + 1, text.end(), bms);
  }
  end = chrono::system_clock::now();
  chrono::duration<long, std::micro> std_bms_time = chrono::duration_cast<chrono::microseconds>(end - start);
  std::println("std::boyer_moore_searcher time: {}", find_time);

  ASSERT_EQ(bm_res->get_mat_pos(), find_pos);
  ASSERT_EQ(std_bm_pos, find_pos);
  std::println("result: {}", bm_res->get_mat_pos());
}