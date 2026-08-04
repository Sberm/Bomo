#include <memory>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>

#include "Match/Engine.h"

namespace fs = boost::filesystem;

/*
 * match a pattern against a directory
 */
TEST(RegexTest, match) {
  // run it through A Pale view of hills
  std::cout << fs::initial_path() << std::endl;
  fs::path path = "test/A_Pale_View_of_Hills.txt";
  std::string patrn = "noo?d";
  Engine engine;
  std::unique_ptr<Result> result = engine.match(path, patrn);
  std::cout << "regex match result:\n";
  std::cout << *result << std::endl;
}
