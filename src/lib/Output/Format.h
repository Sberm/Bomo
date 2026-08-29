// ========================================================
//
//    Howard Chu (c) 2026: howardchu95@gmail.com
// ========================================================

#pragma once

#include <string>
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BLACK "\033[30m"

struct Color {
  const char* code;
};

constexpr Color Red { RED };
constexpr Color Green { GREEN };
constexpr Color Yellow { YELLOW };
constexpr Color Blue { BLUE };
constexpr Color Purple { PURPLE };
constexpr Color Cyan { CYAN };
constexpr Color White { WHITE };
constexpr Color Black { BLACK };
constexpr Color ColorReset { RESET };

class ColorCout {
public:
  std::string color;

  ColorCout(const char *color) {
    this->color = std::string(color);
  }

  template<class T>
  std::ostream& operator<<(T rhs) {
    return std::cout << color << rhs;
  }
};

/* cout << Red << other_stuff; */
std::ostream& operator << (std::ostream& os, const Color& color);
void ColorPrintf(const char* color, const char* fmt, ...);
