#include <vector>
#include <string>
#include <boost/filesystem.hpp>

#include "File.h"

namespace fs = boost::filesystem;

namespace bomo {
  File::File(const fs::path& path) : __path(path) {
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
    return __path.native().compare(f.__path.native()) < 0;
  }
}
