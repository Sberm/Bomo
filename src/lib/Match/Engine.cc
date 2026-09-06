// ========================================================
//  Regex engine
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include <re2/re2.h>

#include "Engine.h"
#include "Output/Result.h"
#include "File/File.h"

std::unique_ptr<Result> Engine::MatchAll(fs::path path) const {
  File file = File(path);
  auto& stream = file.GetStream();
  std::string line;
  auto result = std::make_unique<Result>();
  size_t line_num = 0;

  while (getline(stream, line)) {
    size_t start = 0;
    size_t const end = line.size();
    std::string_view sv(line);
    std::vector<size_t> match_pos;
    while (start < end) {
      size_t match = Find(sv, start, end);
      if (match == NOT_FOUND)
        break;
      match_pos.push_back(match);
      start = match + 1;
    }
    if(!match_pos.empty())
      result->PushBack(LineMatch(line_num, line, std::move(match_pos)));
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
