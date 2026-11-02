// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <vector>
#include <string>
#include <stddef.h>
#include <optional>

#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class LineMatch {
 private:
  size_t line_num_;
  std::string line_;
  std::vector<std::pair<size_t, size_t>> match_ranges_; // {start, end}, end is non-inclusive
 public:
  size_t GetLineNum() const { return line_num_; }
  const std::string& GetLine() const { return line_; }
  const std::vector<std::pair<size_t, size_t>>& GetMatchRanges() const { return match_ranges_; }

  /*
   * TODO: make the line nullable
   */
  LineMatch(size_t line_num, std::optional<std::string> line, std::vector<std::pair<size_t, size_t>>&& match_ranges):
    line_num_(line_num), line_(line.value_or("")), match_ranges_(match_ranges) {}
};

class FileMatch {
 private:
  std::vector<LineMatch> line_matches_;
  fs::path path_;
 public:
  std::vector<LineMatch> const & GetLineMatches() const { return line_matches_; }
  fs::path const & GetPath() const { return path_; }

  FileMatch() {}
  FileMatch(fs::path path) : 
    path_(path)
  {}
  
  void PushBack(const LineMatch& line_match) {
    line_matches_.push_back(line_match);
  }

  operator bool() const { return !line_matches_.empty(); }
};

class Match {
 private:
  std::vector<FileMatch> file_matches_;
 public:
  const std::vector<FileMatch>& GetFileMatches() const { return file_matches_; }

  void PushBack(const FileMatch& file_match) {
    file_matches_.push_back(file_match);
  }
};

std::ostream& operator << (std::ostream& outs, const LineMatch& mat);
std::ostream& operator << (std::ostream& outs, const FileMatch& res);
std::ostream& operator << (std::ostream& outs, const Match& res);
