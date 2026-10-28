// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <print>
#include <re2/set.h>

class Filter {
private:
  re2::RE2::Set pat_set_; // regex patterns

public:
  Filter(std::vector<std::string>&& pats)
    : pat_set_(RE2::DefaultOptions, RE2::UNANCHORED)
  {
    std::string error_msg;
    for (auto pat: pats) {
      if (pat_set_.Add(pat, &error_msg) == -1) {
        std::println("failed to parse file filter regex, err: {}", error_msg);
      }
    }
    if (pat_set_.Compile()) {
      std::println("failed to compile due to OOM");
    }
  }

  const re2::RE2::Set& GetPatSet() noexcept { return pat_set_; }

  bool ShouldFilter(std::string& path) noexcept
  {
    return pat_set_.Match(path, nullptr);
  }
};
