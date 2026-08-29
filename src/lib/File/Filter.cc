// ========================================================
//  Based on rules imposed by .gitignore and so on, filter
//  files.
// 
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================


#include <boost/filesystem.hpp>
#include <string>

namespace fs = boost::filesystem;

class Filter {
private:
  std::vector<fs::path> dirs_;
  std::vector<std::string> pats_; // regex patterns
  std::vector<fs::path> files_;

public:
  Filter(std::vector<fs::path>&& dirs, std::vector<std::string>&& pats, std::vector<fs::path>&& files)
    : dirs_(dirs)
    , pats_(pats)
    , files_(files)
  {}

  const std::vector<fs::path>& GetDirs() { return dirs_; }
  const std::vector<std::string>& GetPats() { return pats_; }
  const std::vector<fs::path>& GetFiles() { return files_; }
};
