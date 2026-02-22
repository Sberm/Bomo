#include <gtest/gtest.h>
#include <string>
#include <boost/filesystem.hpp>
#include <fstream>
#include <cstdio>

#include "File/File.h"

namespace fs = boost::filesystem;

void writeClose(std::ofstream& fs) {
  fs << "moo";
  fs.flush();
  fs.close();
}

void rm(const fs::path dir) {
  fs::remove_all(dir);
  std::printf("%s removed\n", dir.native().c_str());
}

TEST(FileTest, readDir) {
  /*
   *  test_dir
   *    file1.txt
   *    file2.txt
   *    dir1
   *      file3.txt
   */
  fs::path testDir("test_dir");
  fs::path dir1 = testDir / "dir1";
  fs::create_directory(testDir);
  fs::create_directory(dir1);

  std::ofstream file1((testDir / "file1.txt").native());
  std::ofstream file2((testDir / "file2.txt").native());
  std::ofstream file3((dir1 / "file3.txt").native());

  writeClose(file1);
  writeClose(file2);
  writeClose(file3);

  std::vector<bomo::File> files = bomo::readDir(testDir);
  std::sort(files.begin(), files.end(), [](const bomo::File& f1, const bomo::File& f2) {
    return f1.comp(f2);
  });

  std::cout << "Files:" << std::endl;
  for (auto&& file: files)
    std::cout << file.path() << std::endl;

  ASSERT_EQ(files.size(), 4);
  ASSERT_EQ(files[0].path(), "test_dir/dir1");
  ASSERT_EQ(files[1].path(), "test_dir/dir1/file3.txt");
  ASSERT_EQ(files[2].path(), "test_dir/file1.txt");
  ASSERT_EQ(files[3].path(), "test_dir/file2.txt");

  // remove the directory
  rm(testDir);
}


