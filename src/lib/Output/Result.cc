// ========================================================
//  Matching results
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <ostream>

#include "Result.h"

std::ostream& operator << (std::ostream& outs, const LineMatch& mat) {
  const std::vector<size_t>& mat_pos = mat.get_mat_pos();
  size_t n = mat_pos.size();

  outs << mat.get_line_num() << ": " << mat.get_line() << ": ";
  for (size_t i = 0; i < n; ++i) {
    if (i + 1 == n)
      outs << mat_pos[i] << "\n";
    else
      outs << mat_pos[i] << " ";
  }
  return outs;
}

std::ostream& operator << (std::ostream& outs, const Result& res) {
  for (const LineMatch& mat: res.get_mats())
    outs << mat << "\n";
  return outs;
}
