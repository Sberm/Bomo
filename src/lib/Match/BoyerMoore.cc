#include <print>
#include <limits.h> /* UCHAR_MAX */
#include <cassert>
#include <stdint.h>

#include "BoyerMoore.h"

BoyerMoore::BoyerMoore(const std::string& patrn): patrn_(patrn) {
  /*
   * -=-=-=-=-=-=-= Bad character rule (delta1) =-=-=-=-=-=-=-
   * Space complexity is either O(km) where k is the size of alphabet and m is the size
   * of the pattern, delta1[charset][pattern_sz], which records all occurrences; or O(k)
   * and only records the last occurrence of a character.
   * 
   * We choose to do O(k) for space. And the time complexity is O(q + m) where q is the 
   * size of the alphabet.
   * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   */
  // TODO: make patrn_sz_ a separate variable or get it from .size()
  patrn_sz_ = patrn_.size();
  delta1_.fill(patrn_sz_);
  for (int i = 0; i < patrn_sz_; i++)
    delta1_[patrn_[i]] = patrn_sz_ - 1 - i;

  /*
   * -=-=-=-=-=-=-= Good suffix rule (delta2) =-=-=-=-=-=-=-
   * This is an O(m) table generation algorithm by Knuth
   * Reference: Knuth, Donald E.; Morris, James H. Jr.; Pratt, Vaughan R. (1977). 
   * "Fast pattern matching in strings"
   * -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
   */
  delta2_.resize(patrn_sz_);
  std::vector<int> foward(patrn_sz_);
  for (int i = 0; i < patrn_sz_; i++)
    delta2_[i] = 2 * patrn_sz_ - i - 1;
  int j = patrn_sz_ - 1;
  int t = patrn_sz_;
  while (j >= 0) {
      foward[j] = t;
      while (t < (int)patrn_sz_ && patrn_[j] != patrn_[t]) {
        delta2_[t] = std::min(delta2_[t], (int)patrn_sz_ - 1 - j);
        t = foward[t];
      }
      t -= 1;
      j -= 1;
  }
  /* for incomplete prefix, e.g. BCXXXABC */
  for (int i = 0; i <= t; i++)
    delta2_[i] = std::min(delta2_[i], (int)patrn_sz_ + t - i);
}

std::unique_ptr<LineMatch> BoyerMoore::Match(const std::string& text) {
  assert(patrn_sz_ > 0);
  int64_t text_idx = patrn_sz_ - 1;
  int64_t text_sz = std::size(text);
  std::vector<size_t> mats;

  while (text_idx < text_sz) {
    int64_t patrn_idx = patrn_sz_ - 1;

    while (patrn_idx >= 0 && text[text_idx] == patrn_[patrn_idx]) {
      patrn_idx -= 1;
      text_idx -= 1;
    }
    if (patrn_idx <= 0) {
      /* mats are size_t */
      assert(text_idx + 1 >= 0);
      mats.push_back(text_idx + 1);
      text_idx += patrn_sz_ + 1;
    } else {
      // text[text_idx] can be negative
      text_idx += std::max(delta1_[static_cast<unsigned char>(text[text_idx])], delta2_[patrn_idx]);
    }
  }

  // TODO: Line number and pass the line
  return std::make_unique<LineMatch>(114, "", std::move(mats));
}

void BoyerMoore::PrintDelta1() {
  unsigned char ch = 0;
  for (int& d: delta1_) {
    if (d != patrn_sz_)
      std::println("{:c}: {}", ch, d);
    ch += 1;
  }
}

void BoyerMoore::PrintDelta2() {
  for (int& d: delta2_)
    std::print("{} ", d);
  std::println();
}
