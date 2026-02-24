#include <vector>
#include <string>
#include <stddef.h>

class LineMatch {
  size_t line_num;
  std::string line;
  std::vector<size_t> mat_poses; // matched positions in text
};

class Result {
  std::vector<LineMatch> mats;
};
