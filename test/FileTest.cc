#include <gtest/gtest.h>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <cstdio>
#include <algorithm> // std::sort

#include "File/File.h"

namespace fs = boost::filesystem;

void WriteClose(std::ofstream& fs) {
  fs << "moo";
  fs.flush();
  fs.close();
}

void rm(const fs::path dir) {
  fs::remove_all(dir);
  std::printf("%s removed\n", dir.native().c_str());
}

TEST(FileTest, ReadDir) {
  /*
   *  test_dir
   *    file1.txt
   *    file2.txt
   *    dir1
   *      file3.txt
   */
  fs::path test_dir("test_dir");
  fs::path dir1 = test_dir / "dir1";
  fs::create_directory(test_dir);
  fs::create_directory(dir1);

  std::ofstream file1((test_dir / "file1.txt").native());
  std::ofstream file2((test_dir / "file2.txt").native());
  std::ofstream file3((dir1 / "file3.txt").native());

  WriteClose(file1);
  WriteClose(file2);
  WriteClose(file3);

  std::vector<File> files = ReadDir(test_dir);
  std::sort(files.begin(), files.end(), [](const File& f1, const File& f2) {
    return f1.Comp(f2);
  });

  std::cout << "Files:" << std::endl;
  for (auto&& file: files)
    std::cout << file.GetPath() << std::endl;

  ASSERT_EQ(files.size(), 4);
  ASSERT_EQ(files[0].GetPath(), "test_dir/dir1");
  ASSERT_EQ(files[1].GetPath(), "test_dir/dir1/file3.txt");
  ASSERT_EQ(files[2].GetPath(), "test_dir/file1.txt");
  ASSERT_EQ(files[3].GetPath(), "test_dir/file2.txt");

  // remove the directory
  rm(test_dir);
}

TEST(FileTest, NotFoundShouldFail) {
  fs::path path = "GARbagegaRBage.garbage";
  bool failed{false};
  try {
    File file(path);
  } catch (...) {
    failed = true;
    std::cout << "this test is expected to fail" << std::endl;
  }
  ASSERT_TRUE(failed);
}
