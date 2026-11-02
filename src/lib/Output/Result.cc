// ========================================================
//  Matching results
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <ostream>
#include <print>

#include "Result.h"
#include "Output/Format.h"

const bool show_column = true;

std::ostream& operator << (std::ostream& outs, const Match& matches) {
  auto file_matches = matches.GetFileMatches();
  for (auto file_match: file_matches) {
    outs << file_match;
  }
  return outs;
}

std::ostream& operator << (std::ostream& outs, const LineMatch& line_match) {
  const std::vector<std::pair<size_t, size_t>>& match_ranges = line_match.GetMatchRanges();
  size_t n = match_ranges.size();
  outs << Red << line_match.GetLineNum() << ": " << ColorReset;

  auto line = line_match.GetLine();
  size_t start = 0;
  for (size_t i = 0; i < n; i++) {
    auto [range_start, range_end] = match_ranges[i];
    outs << std::string_view(line.begin() + start, line.begin() + range_start);
    outs << Red << std::string_view(line.begin() + range_start, line.begin() + std::min(range_end, line.size())) << ColorReset;
    start = range_end;
  }
  if (line.begin() + start != line.end()) {
    outs << std::string_view(line.begin() + start, line.end());
    start = line.size();
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

  outs << "\n";

  return outs;
}

std::ostream& operator << (std::ostream& outs, const FileMatch& res) {
  outs << res.GetPath().relative_path().c_str() << ":\n";
  for (const LineMatch& mat: res.GetLineMatches())
    outs << mat;
  return outs;
}
