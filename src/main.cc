#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "Match/Engine.h"
#include "Output/Result.h"
#include "Misc/Util.h"

#define HELP "help"
#define PAT  "pattern"
#define DIRC  "directory"
#define MADELEINE "madeleine"

bool const bmdebug = false;

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int ac, char **av)
{
  po::options_description desc("Bomo command arguments");
  desc.add_options()
    ("help", "print this message")
    ((std::string(PAT) + ",p").c_str(), po::value<std::string>(), "search pattern")
    // don't know how this works yet
    ((std::string(DIRC) + ",d").c_str(), po::value<std::vector<std::string>>(), "directory to search from")
    ((std::string(MADELEINE)).c_str(), "search for the string \'madeleine\'");
  po::positional_options_description pos_opt;
  po::variables_map var_map;

  std::string pattern;
  std::vector<std::string> paths;

  /* <pattern, directory> */
  pos_opt.add(PAT, 1).add(DIRC, 2);
  try {
    po::store(po::command_line_parser(ac, av).options(desc).positional(pos_opt).run(), var_map);
  } catch (...) {
    std::cout << desc << std::endl;
    return 0;
  }
  po::notify(var_map);

  /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
  /* =x=x=x=x=x=x=x=x=x=x WARNING: lots of options =x=x=x=x=x=x=x=x=x=x */
  /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
  if (var_map.count(HELP)) {
    std::cout << desc << std::endl;
    return 0;
  }
  if (var_map.count(PAT)) {
    pattern = var_map[PAT].as<std::string>();
  }
  if (var_map.count(DIRC)) {
    paths = var_map[DIRC].as<std::vector<std::string>>();
  } else {
    paths.push_back(".");
  }
  if (var_map.count(MADELEINE)) {
    Util::Madeleine();
    pattern = "(?i)madeleine";
  }
  /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
  /* =x=x=x=x=x=x=x=x=x=x=x options handling ends =x=x=x=x=x=x=x=x=x=x= */
  /* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

  /* bomo has to have a pattern */
  if (!pattern.empty()) {
    if (bmdebug) {
      std::println("pattern: \"{}\"", pattern);
      std::println("paths: \n{}", paths);
    }

    /* let it rip!!! */
    Engine engine(pattern);
    for (auto path: paths) {
      if (fs::is_directory(fs::path(path))) {
        std::unique_ptr<Match> result = engine.MatchDir(fs::path(path));
        if (*result)
          std::cout << *result;
      } else {
        std::unique_ptr<FileMatch> result = engine.MatchFile(fs::path(path));
        if (*result)
          std::cout << *result;
      }
    }
  } else {
    std::println("search pattern is empty");
    std::cout << desc << std::endl;
  }
  
  return 0;
}
