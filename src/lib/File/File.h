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

  File(const fs::path& path)
    : path_(path)
  {
    stream_ = std::ifstream(path.string().c_str(), std::ifstream::in);
    if (stream_.fail())
      throw std::runtime_error("failed to open stream of file " + path.string());
  }

  std::ifstream& GetStream() { return stream_; }
  fs::path       GetPath()   { return path_; }
  bool           Comp(const File& f) const;
};

std::vector<File> ReadDir(const fs::path& dir);
