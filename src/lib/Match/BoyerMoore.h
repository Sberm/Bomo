#pragma once

#include <string>
#include <memory>
#include <map>
#include <limits.h> /* UCHAR_MAX */

#include "Output/Result.h"

class BoyerMoore {
  std::string      patrn_;
  std::array<int,  UCHAR_MAX> delta1_;
  std::vector<int> delta2_;
  size_t           patrn_sz_;
 public:
  BoyerMoore(const std::string& patrn);
  int Delta1CharIdx(char c, int idx);
  std::unique_ptr<LineMatch> Match(const std::string& text);
  void PrintDelta1();
  void PrintDelta2();
  std::array<int, UCHAR_MAX> GetDelta1() { return delta1_; }
  std::vector<int> GetDelta2() { return delta2_; }
  size_t GetPatrnSz() { return patrn_sz_; }
};

std::ostream& operator << (std::ostream& ostream, BoyerMoore &bm);
