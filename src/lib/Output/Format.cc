// ========================================================
//  Output formatter
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#include "Format.h"

#include <cstdio>
#include <stdarg.h>
#include <ostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Color& color) {
  return os << color.code;
}

void color_printf(const char* color, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  std::printf("%s", color);
  std::vprintf(fmt, args);
  std::printf("%s", RESET);
  va_end(args);
}