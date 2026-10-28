#include <gtest/gtest.h>
#include <string>
#include <boost/filesystem.hpp>
#include <cstdio>

#include "File/Filter.h"

namespace fs = boost::filesystem;

void WriteClose(std::ofstream& f) {
  f << "moo";
  f.flush();
  f.close();
}

void rm(const fs::path dir) {
  fs::remove_all(dir);
  std::printf("%s removed\n", dir.native().c_str());
}

TEST(FilterTest, ShouldFilter) {
  /*
   *  test_dir
   *    file1.txt
   *    file2.txt
   *    file3.txt
   *    bar2.txt
   *    dir1
   *      foo1.txt
   *      foo2.txt
   *    dir2
   *      foo1.txt
   *      foo2.txt
   */
  fs::path test_dir("test_dir");
  fs::path dir1 = test_dir / "dir1";
  fs::path dir2 = test_dir / "dir2";
  fs::create_directory(test_dir);
  fs::create_directory(dir1);
  fs::create_directory(dir2);

  std::ofstream file1((test_dir / "file1.txt").native());
  std::ofstream file2((test_dir / "file2.txt").native());
  std::ofstream file3((test_dir / "file3.txt").native());
  std::ofstream bar2((test_dir / "bar2.txt").native());
  std::ofstream dir1_foo1((dir1 / "foo1.txt").native());
  std::ofstream dir1_foo2((dir1 / "foo2.txt").native());
  std::ofstream dir2_foo1((dir2 / "foo1.txt").native());
  std::ofstream dir2_foo2((dir2 / "foo2.txt").native());

  WriteClose(file1);
  WriteClose(file2);
  WriteClose(file3);
  WriteClose(bar2);
  WriteClose(dir1_foo1);
  WriteClose(dir1_foo2);
  WriteClose(dir2_foo1);
  WriteClose(dir2_foo2);

  // files that end with 2, or dir2/*1.txt
  std::string pat1 = R"(.*2\.txt)";
  std::string pat2 = R"(dir2/.*1\.txt)";
  Filter filter({pat1, pat2});
  auto& pat_set = filter.GetPatSet();
  ASSERT_EQ(pat_set.Size(), 2);

  // remove the directory
  rm(test_dir);
}
