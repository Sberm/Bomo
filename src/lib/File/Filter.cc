/*
 * Based on rules imposed by .gitignore and so on, filter
 * files.
 *
 *   Howard Chu (c) 2026: howardchu95@gmail.com
 */

#include <boost/filesystem.hpp>
#include <string>

namespace fs = boost::filesystem;

class Filter {
private:
  std::vector<fs::path> dirs;
  std::vector<std::string> pats; // regex patterns
  std::vector<fs::path> files;

public:
  Filter(std::vector<fs::path>& dirs, std::vector<std::string>& pats, std::vector<fs::path>& files)
  : dirs(dirs), pats(pats), files(files)
  {}

  const std::vector<fs::path>& getDirs() { return dirs; }
  const std::vector<std::string>& getPats() { return pats; }
  const std::vector<fs::path>& getFiles() { return files; }
};
