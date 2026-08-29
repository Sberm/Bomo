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

/* returns in lexicographical order */
bool File::Comp(const File& f) const {
  return path_.native().compare(f.path_.native()) < 0;
}

/* Read all the files from a directory recursively */
std::vector<File> ReadDir(const fs::path& dir) {
  std::vector<File> files;

  for (auto&& iter: fs::recursive_directory_iterator(dir))
    files.push_back(File(iter.path()));

  return files;
}
