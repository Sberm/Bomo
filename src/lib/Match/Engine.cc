// ========================================================
//  Regex engine
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include "re2/re2.h"

#include "Engine.h"
#include "Output/Result.h"
#include "File/File.h"

namespace fs = boost::filesystem;

// return true if there's any captures
// TODO: make this print as soon as there's a match
bool Engine::MatchStrAll(std::string_view sv, std::vector<std::pair<size_t, size_t>>& match_ranges) const {
  std::string_view capture;
  std::string_view save = sv;
  bool captured = false;
  while (RE2::FindAndConsume(&sv, re2_, &capture)) {
    captured = true;
    size_t start = capture.data() - save.data();
    match_ranges.push_back({start, start + capture.size()}); 
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
