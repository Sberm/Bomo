// ========================================================
//  Matching results
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <ostream>
#include <print>

#include "Result.h"
#include "Output/Format.h"
#include "Misc/Util.h"

const bool show_column = false;

std::ostream& operator << (std::ostream& outs, Match const & match) {
  auto file_matches = match.GetFileMatches();
  for (auto file_match: file_matches) {
    outs << file_match;
  }
  return outs;
}

std::ostream& operator << (std::ostream& outs, LineMatch const & line_match) {
  const std::vector<std::pair<size_t, size_t>>& match_ranges = line_match.GetMatchRanges();
  size_t n = match_ranges.size();
  outs << Green << line_match.GetLineNum() << ": " << ColorReset;

  auto line = line_match.GetLine();
  size_t unmatched_start = 0;
  for (size_t i = 0; i < n; i++) {
    auto [range_start, range_end] = match_ranges[i];
    if (range_start == range_end) {
      /* e.g. 'a*' */
      size_t const next_char_idx = Util::NextChar(line, range_start);
      outs << std::string_view(line.begin() + range_start, line.begin() + next_char_idx);
      unmatched_start = next_char_idx;
    } else {
      outs << std::string_view(line.data() + unmatched_start, line.data() + range_start);
      outs << Red << std::string_view(line.data() + range_start, line.data() + range_end) << ColorReset;
      unmatched_start = range_end;
    }
  }
  if (line.begin() + unmatched_start < line.end()) {
    outs << std::string_view(line.data() + unmatched_start, line.data() + line.size());
    unmatched_start = line.size();
  }

  if (show_column) {
    outs << ": ";
    for (size_t i = 0; i < n; ++i) {
      if (i + 1 == n)
        outs << match_ranges[i].first + 1;
      else
        outs << match_ranges[i].first + 1 << ' ';
    }
  } 

  outs << '\n';
  return outs;
}

std::ostream& operator << (std::ostream& outs, FileMatch const & res) {
  outs << Yellow << res.GetPath().relative_path().c_str() << ColorReset << ":\n";
  for (const LineMatch& mat: res.GetLineMatches())
    outs << mat;
  outs << '\n';
  return outs;
}
