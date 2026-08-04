#pragma once

#include <string>
#include <memory>
#include <map>
#include <limits.h> /* UCHAR_MAX */

#include "Output/Result.h"

class BoyerMoore {
  std::string patrn_;
  std::array<int, UCHAR_MAX> delta1_;
  std::vector<int> delta2_;
  size_t patrn_sz_;
 public:
  BoyerMoore(const std::string& patrn);
  int delta1_char_idx(char c, int idx);
  std::unique_ptr<LineMatch> match(const std::string& text);
  void print_delta1();
  void print_delta2();
  std::array<int, UCHAR_MAX> get_delta1() { return delta1_; }
  std::vector<int> get_delta2() { return delta2_; }
  size_t get_patrn_sz() { return patrn_sz_; }
};

std::ostream& operator << (std::ostream& ostream, BoyerMoore &bm);