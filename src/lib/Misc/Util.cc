#include <stddef.h>
#include <string_view>
#include <stddef.h>

#include "Util.h"

namespace Util {
  size_t NextChar(std::string_view const sv, size_t const start) {
    unsigned char ch = sv[start];
    if (ch >> 7 == 0) {
      return start + 1;
    } else if (ch >> 5 == 0b110) {
      return start + 2;
    } else if (ch >> 4 == 0b1110) {
      return start + 3;
    } else {
      return start + 4;
    }
  }
} /* namespace util */
