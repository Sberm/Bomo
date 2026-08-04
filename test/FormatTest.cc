#include <iostream>

#include <gtest/gtest.h>

#include "Output/Format.h"

TEST(FormatTest, color_cout) {
  std::cout << Red << "I should be red" << ColorReset << std::endl;
  std::cout << Green << "I should be Green" << ColorReset << std::endl;
  std::cout << Yellow << "I should be yellow" << ColorReset << std::endl;
  std::cout << Blue << "I should be blue" << ColorReset << std::endl;
  std::cout << Purple << "I should be purple" << ColorReset << std::endl;
  std::cout << Cyan << "I should be cyan" << ColorReset << std::endl;
  std::cout << White << "I should be white" << ColorReset << std::endl;
  std::cout << Black << "I should be black" << ColorReset << std::endl;
}

TEST(FormatTest, color_printf) {
  std::size_t szt = 99999999999;
  short st = 18;
  color_printf(RED, "I should be red\n");
  color_printf(GREEN, "I should be green %d\n", 114514);
  color_printf(YELLOW, "I should be yellow, %s\n", "fam");
  color_printf(BLUE, "I should be blue %.2f\n", 3.14f);
  color_printf(PURPLE, "I should be purple double: %lf\n", 3.141592653);
  color_printf(CYAN, "I should be cyan %hd\n", st);
  color_printf(WHITE, "I should be white %zd\n", szt);
  color_printf(BLACK, "I should be black %llu\n", 88888888ULL);
}

TEST(FormatTest, class_cout) {
  ColorCout(BLUE) << "I should be blue, I like sk" << 8 << "ting" << RESET << std::endl;
  ColorCout(CYAN) << "I should be cyan, I like tr" << 3 << "s" << RESET << std::endl;
}
