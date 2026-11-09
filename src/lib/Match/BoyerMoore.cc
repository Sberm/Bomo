#include <print>
#include <limits.h> /* UCHAR_MAX */
#include <cassert>
#include <stdint.h>
#include <string.h>

#include "BoyerMoore.h"

// TODO: static-able?

BoyerMoore::BoyerMoore(std::string const & pattern): pattern_(pattern) {
  /*
   * -=-=-=-=-=-=-=-=-=-=-= Bad character rule (delta1) -=-=-=-=-=-=-=-=-=-=-=
   * Only the last occurrence is necessary
   * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   */
  size_t pattern_sz = pattern_.size();
  delta1_.fill(-1);
  for (int i = 0; i < pattern_sz; i++)
    delta1_[static_cast<unsigned char>(pattern_[i])] = i;

  /*
   * -=-=-=-=-=-=-=-=-=-=-=-= Good suffix rule (delta2) =-=-=-=-=-=-=-=-=-=-=-
   * This is an O(m) table generation algorithm by Knuth. Reference: Knuth,
   * Donald E.; Morris, James H. Jr.; Pratt, Vaughan R. (1977). "Fast pattern
   * matching in strings"
   * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   */
  delta2_.resize(pattern_sz);
  std::vector<int> foward(pattern_sz);
  for (int i = 0; i < pattern_sz; i++)
    delta2_[i] = 2 * pattern_sz - i - 1;
  int j = pattern_sz - 1;
  int t = pattern_sz;
  while (j >= 0) {
      foward[j] = t;
      while (t < (int)pattern_sz && pattern_[j] != pattern_[t]) {
        delta2_[t] = std::min(delta2_[t], (int)pattern_sz - 1 - j);
        t = foward[t];
      }
      t -= 1;
      j -= 1;
  }
  /* for incomplete prefix, e.g. BCXXXABC */
  for (int i = 0; i <= t; i++)
    delta2_[i] = std::min(delta2_[i], (int)pattern_sz + t - i);
}

bool BoyerMoore::FindAndConsume(std::string_view const text, size_t const start, size_t const end, std::string_view * capture) const {
  size_t pattern_sz = pattern_.size();
  if (pattern_sz == 0 || start > end || end - start < pattern_sz)
    return false;
  char const * data_start = text.data() + start;
  char const * data = data_start;
  char const first_char = pattern_[0];
  char const * last = text.data() + end - pattern_sz;
  while (data <= last) {
    data = static_cast<char const *>(memchr(data, first_char, last - data + 1));
    if (!data) {
      return false;
    }
    if (!memcmp(data, pattern_.data(), pattern_sz)) {
      *capture = std::string_view(data, data + pattern_sz);
      return true;
    } else {
      data++;
    }
  }
  return false;
}

bool BoyerMoore::FindAndConsume2(std::string_view const text, size_t const start, size_t const end, std::string_view * capture) const {
  size_t pattern_sz = pattern_.size();
  int64_t text_idx = start + pattern_sz - 1;

  while (text_idx < end) {
    int64_t pattern_idx = pattern_sz - 1;
    int64_t save = text_idx;

    while (pattern_idx >= 0 && text[text_idx] == pattern_[pattern_idx]) {
      pattern_idx -= 1;
      text_idx -= 1;
    }
    if (pattern_idx < 0) {
      *capture = std::string_view(text.begin() + text_idx + 1,
                                  text.begin() + text_idx + 1 + pattern_sz);
      return true;
    } else {
      text_idx = std::max({
          save + 1LL,
          save + pattern_idx - delta1_[static_cast<unsigned char>(text[text_idx])],
          text_idx + static_cast<int64_t>(delta2_[pattern_idx])
      });
    }
  }
  return false;
}

void BoyerMoore::PrintDelta1() const {
  unsigned char ch = 0;
  for (auto d: delta1_) {
    if (d != GetPatternSize())
      std::println("{:c}: {}", ch, d); 
    ch += 1;
  }
}

void BoyerMoore::PrintDelta2() const {
  for (auto d: delta2_)
    std::print("{} ", d);
  std::println();
}
