#include <string>
#include <print>
#include <gtest/gtest.h>

#include "re2/re2.h"

TEST(Re2Test, Re2Test) {
  std::string pattern = "fo[o]*bar";
  std::string text = "foobarfooooobarfoobaristfobara";
  re2::RE2 re2(pattern);
  std::string_view submatch;
  size_t start = 0;
  
  while (re2.Match(text, start, text.size(), re2::RE2::UNANCHORED, &submatch, 1)) {
    std::println("submatch {}", submatch);
    start += submatch.size();
  }
}
