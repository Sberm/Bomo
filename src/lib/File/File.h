// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <memory>

namespace fs = boost::filesystem;

class File {
 private:
  fs::path      path_;
  std::ifstream stream_;

 public:
  File(const fs::path& path);
  std::ifstream& getStream() { return stream_; }
  fs::path       getPath()   { return path_; }
  bool           comp(const File& f) const;
};

std::vector<File> readDir(const fs::path& dir);