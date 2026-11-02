#pragma once

#include <string_view>
#include <stddef.h>

namespace Util {
  size_t NextChar(std::string_view const sv, size_t const start);

  void Madeleine();

} /* namespace util */
