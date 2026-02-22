#pragma once

#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <memory>

namespace fs = boost::filesystem;

namespace bomo {

  struct Result {
  };

  class File {
  private:
      fs::path      __path;
      std::ifstream __stream;

  public:
      File(const fs::path& path);
      std::ifstream& stream() { return __stream; }
      fs::path       path()   { return __path; }
      bool           comp(const File& f) const;
  };

  std::vector<File> readDir(const fs::path& dir);
} // namespace bomo
