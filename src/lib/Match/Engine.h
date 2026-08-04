// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <memory>
#include <boost/filesystem.hpp>

#include "Output/Result.h"

namespace fs = boost::filesystem;

class Engine {
 public:
  // TODO: result needs a comp predicate
  std::unique_ptr<Result> match(fs::path dir, std::string pat);
  std::unique_ptr<Result> match(std::string& text, std::string& pat);
};