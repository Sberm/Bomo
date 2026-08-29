// ========================================================
//  Regex engine
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <re2/re2.h>

#include "Engine.h"
#include "Output/Result.h"
#include "File/File.h"

// TODO: let's use a reference
std::unique_ptr<Result> Engine::MatchAll(fs::path path) const {
  File file = File(path);
  auto& stream = file.GetStream();
  std::string line;
  auto result = std::make_unique<Result>();
  size_t line_num = 0;

  // TODO: multiple matches
  while (getline(stream, line)) {
    if (RE2::PartialMatch(line, re2_))
        result->PushBack(LineMatch(line_num, line, {}));
    line_num++;
  }
  return result;
}

size_t Engine::Find(std::string_view sv, size_t st, size_t end) const {
  std::string_view matched;
  re2_.Match(sv, st, end, RE2::UNANCHORED, &matched, 1);
  if (!matched.data())
    return NOT_FOUND;
  return matched.data() - sv.data();
}
