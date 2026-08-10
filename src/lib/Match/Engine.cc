// ========================================================
//  Regex engine
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <memory>
#include <string>

#include <re2/re2.h>

#include "Engine.h"
#include "Output/Result.h"
#include "File/File.h"

// TODO: let's use a reference
std::unique_ptr<Result> Engine::match(fs::path path, std::string pat) {
  File file = File(path);
  auto& stream = file.getStream();
  std::string line;
  auto result = std::make_unique<Result>();
  size_t line_num = 0;

  // TODO: multiple matches
  while (getline(stream, line)) {
    if (RE2::PartialMatch(line, pat))
        result->push_back(LineMatch(line_num, line, {}));
    line_num++;
  }
  return result;
}
