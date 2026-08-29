// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <memory>
#include <boost/filesystem.hpp>
#include <string_view>

#include "re2/prog.h"

#include "Output/Result.h"

namespace fs = boost::filesystem;

class Engine {
 public:

  static const size_t NOT_FOUND = SIZE_MAX;

  Engine(const std::string& patrn)
    : re2_(patrn)
  {}

  // TODO: result needs a comp predicate
  std::unique_ptr<Result> MatchAll(fs::path path) const;

  /*
   * Uses raw pointers, this is not recommended.
   * When find cannot find the next occurrence, it will return NULL.
   */
  size_t Find(std::string_view sv, size_t st, size_t end) const;

 private:
  re2::RE2 re2_;
};
