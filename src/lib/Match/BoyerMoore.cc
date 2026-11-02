#include <print>
#include <limits.h> /* UCHAR_MAX */
#include <cassert>
#include <stdint.h>

#include "BoyerMoore.h"

// TODO: static-able?

BoyerMoore::BoyerMoore(std::string const & pattern): pattern_(pattern) {
  /*
   * -=-=-=-=-=-=-=-=-=-=-= Bad character rule (delta1) -=-=-=-=-=-=-=-=-=-=-=
   * Space complexity is either O(km) where k is the size of alphabet and m is
   * the size of the pattern, delta1[charset][pattern_sz], which records all
   * occurrences; or O(k) and only records the last occurrence of a character.
   * 
   * We choose to do O(k) for space. And the time complexity is O(q + m) where
   * q is the size of the alphabet.
   * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   */
  // TODO: make pattern_sz a separate variable or get it from .size()
  size_t pattern_sz = pattern_.size();
  delta1_.fill(pattern_sz);
  for (int i = 0; i < pattern_sz; i++)
    delta1_[pattern_[i]] = pattern_sz - 1 - i;

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

// match the internal pattern_ member against text
bool BoyerMoore::FindAndConsume(const std::string_view text, std::string_view * capture) const {
  size_t pattern_sz = pattern_.size();
  int64_t text_idx = pattern_sz - 1;
  int64_t text_sz = std::size(text);
  std::vector<std::pair<size_t, size_t>> match_ranges;

  while (text_idx < text_sz) {
    int64_t pattern_idx = pattern_sz - 1;

    while (pattern_idx >= 0 && text[text_idx] == pattern_[pattern_idx]) {
      pattern_idx -= 1;
      text_idx -= 1;
    }
    if (pattern_idx <= 0) {
      assert(text_idx + 1 >= 0);
      // match_ranges.push_back({text_idx + 1, text_idx + 1 + pattern_sz});
      *capture = std::string_view(text.begin() + text_idx + 1,
                                  text.begin() + text_idx + 1 + pattern_sz);
      text_idx += pattern_sz + 1;
      return true;
    } else {
      // text[text_idx] can be negative
      text_idx += std::max(delta1_[static_cast<unsigned char>(text[text_idx])], delta2_[pattern_idx]);
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
