// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <memory>
#include <boost/filesystem.hpp>
#include <string_view>
#include <format>

#include <print>

#include "re2/re2.h"

#include "Output/Result.h"
#include "BoyerMoore.h"

namespace fs = boost::filesystem;

class Engine {
 public:
  static const size_t NOT_FOUND = SIZE_MAX;

  // plain_text == true -> no compilation
  // plain_text == false -> if there's no regex, or if the compilation failed, just use plain text
  Engine(std::string const & pattern, bool const explicit_plain_text = false)
    : pattern_(pattern)
    , parenthesized_pattern_(std::format("({})", pattern))
    , re2_(true ? parenthesized_pattern_ : pattern_) /* no need to parse a pattern if regex is not used */
                                                     /* no need to capture if only file names are printed */
    , bm(pattern)
  {
    // TODO: test me
    std::println("pattern {} unquoted {}", pattern, re2::RE2::QuoteMeta(pattern));
    if (!explicit_plain_text || re2::RE2::QuoteMeta(pattern) == pattern) {
      plain_text_ = true;
    } else {
      plain_text_ = false;
    }
  }

  std::unique_ptr<FileMatch> MatchFile(fs::path const & path) const;
  std::unique_ptr<Match> MatchDir(fs::path const & path) const;
  bool MatchStrAll(std::string_view sv, std::vector<std::pair<size_t, size_t>>& match_ranges) const;
  std::string GetPattern() { return pattern_; }
  std::string GetParenthesizedPattern() { return parenthesized_pattern_; }

 private:
  const std::string pattern_;
  const std::string parenthesized_pattern_;
  re2::RE2 re2_;
  BoyerMoore bm;
  bool plain_text_;
};
