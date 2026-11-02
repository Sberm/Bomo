// ========================================================
//  Regex engine
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include "re2/re2.h"

#include "Engine.h"
#include "Output/Result.h"
#include "File/File.h"
#include "Misc/Util.h"

namespace fs = boost::filesystem;

// TODO: make this print as soon as there's a match
// return true if there's any captures
bool Engine::MatchStrAll(std::string_view sv, std::vector<std::pair<size_t, size_t>>& match_ranges) const {
  std::string_view capture;
  bool captured = false;
  size_t start = 0;
  while (start < sv.size() && re2_.Match(sv, start, sv.size(), re2::RE2::UNANCHORED, &capture, 1)) {
    // for example, a* matches cde, but matched is empty
    if (capture.empty()) {
      match_ranges.push_back({start, start}); 
      start = Util::NextChar(sv, start);
      captured = true;
      continue;
    }
    size_t match_start = capture.data() - sv.data();
    size_t match_end = match_start + capture.size();
    match_ranges.push_back({match_start, match_end}); 
    start = match_end;
    captured = true;
  }
  return captured;
}

std::unique_ptr<Match> Engine::MatchDir(fs::path const & path) const {
  auto result = std::make_unique<Match>();
  fs::recursive_directory_iterator it(path);
  for (; it != end(it); it++) {
    if (!it->is_directory()) {
      auto match_file = MatchFile(it->path());
      if (*match_file)
        result->PushBack(*match_file);
    }
  }
  return result;
}

std::unique_ptr<FileMatch> Engine::MatchFile(fs::path const & path) const {
  File file = File(path);
  auto& stream = file.GetStream();
  std::string line;
  auto result = std::make_unique<FileMatch>(path);
  size_t line_num = 0;

  while (getline(stream, line)) {
    std::string_view sv(line);
    std::vector<std::pair<size_t, size_t>> match_ranges;
    if(MatchStrAll(sv, match_ranges)) {
      result->PushBack(LineMatch(line_num, line, std::move(match_ranges)));
    }
    line_num++;
  }
  return result;
}
