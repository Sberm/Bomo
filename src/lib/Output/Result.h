// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <vector>
#include <string>
#include <stddef.h>
#include <optional>

class LineMatch {
 private:
  size_t line_num_;
  std::string line_;
  std::vector<size_t> mat_pos_; // matched positions in text
 public:
  size_t get_line_num() const { return line_num_; }
  const std::string& get_line() const { return line_; }
  const std::vector<size_t>& get_mat_pos() const { return mat_pos_; }

  /*
   * TODO: make the line nullable
   */
  LineMatch(size_t line_num, std::optional<std::string> line, std::vector<size_t>&& mat_pos):
    line_num_(line_num), line_(line.value_or("")), mat_pos_(mat_pos) {}
};

class Result {
 private:
  std::vector<LineMatch> mats_;
 public:
  const std::vector<LineMatch>& get_mats() const { return mats_; }

  Result() {}
  
  void push_back(const LineMatch& line_match) {
    mats_.push_back(line_match);
  }
};

std::ostream& operator << (std::ostream& outs, const LineMatch& mat);
std::ostream& operator << (std::ostream& outs, const Result& res);
