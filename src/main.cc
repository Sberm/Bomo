#include <iostream>
#include <vector>
#include <string>
#include <print>
#include <memory>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "Match/Engine.h"
#include "Output/Result.h"

#define PAT_KEY "pattern"
#define DIR_KEY "directory"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int ac, char **av)
{
  po::options_description desc("Available options");
  desc.add_options()
    ("help", "print this message")
    ("pattern,p", po::value<std::string>(), "search pattern")
    ("directory,d", po::value<std::vector<std::string>>(), "directory to search from");

  // first pattern string, second directory
  po::positional_options_description pos_opt;
  pos_opt.add(PAT_KEY, 1).add(DIR_KEY, -1);

  po::variables_map vm;
  po::store(po::command_line_parser(ac, av).options(desc).positional(pos_opt).run(), vm);
  po::notify(vm);

  if (vm.count(PAT_KEY) && vm.count(DIR_KEY)) {
    auto pat_s = vm[PAT_KEY].as<std::string>();
    auto dirs = vm[DIR_KEY].as<std::vector<std::string>>();
    std::println("pattern: \"{}\"", pat_s);
    std::println("directories: \n{}", dirs);
    Engine engine;
    // for simplicity use the first directory
    std::unique_ptr<Result> result = engine.match(fs::path(dirs[0]), pat_s);
    std::println("regex match result:\n");
    std::cout << *result << "\n";
  } else {
    std::println("enter pattern and directory");
  }
  
  return 0;
}
