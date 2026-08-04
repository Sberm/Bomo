// ========================================================
//  File operations
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <vector>
#include <string>
#include <fstream>
#include <boost/filesystem.hpp>
#include <iostream>

#include "File.h"

namespace fs = boost::filesystem;

File::File(const fs::path& path):
  path_(path) {
    stream_ = std::ifstream(path.string().c_str(), std::ifstream::in);
    if (stream_.fail())
      throw std::runtime_error("failed to open stream of file " + path.string());
  }

/* Read all the files from a directory recursively */
std::vector<File> readDir(const fs::path& dir) {
  std::vector<File> files;

  for (auto&& iter: fs::recursive_directory_iterator(dir))
    files.push_back(File(iter.path()));

  return files;
}

/* returns in lexicographical order */
bool File::comp(const File& f) const {
  return path_.native().compare(f.path_.native()) < 0;
}
