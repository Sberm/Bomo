#pragma once

#include <string>
#include <memory>
#include <map>
#include <limits.h> /* UCHAR_MAX */

#include "Output/Result.h"

class BoyerMoore {
 private:
  std::string const pattern_;
  std::array<int,  UCHAR_MAX> delta1_;
  std::vector<int> delta2_;
 public:
  BoyerMoore(std::string const & pattern);
  int Delta1CharIdx(char c, int idx) const;
  /* linear string search */
  bool FindAndConsume(std::string_view const text, size_t const start, size_t const end, std::string_view * capture) const;
  /* the real BoyerMoore */
  bool FindAndConsume2(std::string_view const text, size_t const start, size_t const end, std::string_view * capture) const;
  void PrintDelta1() const;
  void PrintDelta2() const;
  std::array<int, UCHAR_MAX> GetDelta1() const { return delta1_; }
  std::vector<int> GetDelta2() const { return delta2_; }
  size_t GetPatternSize() const { return pattern_.size(); }
  std::string GetPattern() const { return pattern_; }
};

std::ostream& operator << (std::ostream& ostream, BoyerMoore &bm);
