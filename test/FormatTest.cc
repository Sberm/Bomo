#include <iostream>

#include <gtest/gtest.h>

#include "Output/Format.h"

TEST(FormatTest, ColorCout) {
  std::cout << Red << "I should be red" << ColorReset << std::endl;
  std::cout << Green << "I should be Green" << ColorReset << std::endl;
  std::cout << Yellow << "I should be yellow" << ColorReset << std::endl;
  std::cout << Blue << "I should be blue" << ColorReset << std::endl;
  std::cout << Purple << "I should be purple" << ColorReset << std::endl;
  std::cout << Cyan << "I should be cyan" << ColorReset << std::endl;
  std::cout << White << "I should be white" << ColorReset << std::endl;
  std::cout << Black << "I should be black" << ColorReset << std::endl;
}

TEST(FormatTest, ColorPrintf) {
  std::size_t szt = 99999999999;
  short st = 18;
  ColorPrintf(RED, "I should be red\n");
  ColorPrintf(GREEN, "I should be green %d\n", 114514);
  ColorPrintf(YELLOW, "I should be yellow, %s\n", "fam");
  ColorPrintf(BLUE, "I should be blue %.2f\n", 3.14f);
  ColorPrintf(PURPLE, "I should be purple double: %lf\n", 3.141592653);
  ColorPrintf(CYAN, "I should be cyan %hd\n", st);
  ColorPrintf(WHITE, "I should be white %zd\n", szt);
  ColorPrintf(BLACK, "I should be black %llu\n", 88888888ULL);
}

TEST(FormatTest, ClassCout) {
  ColorCout(BLUE) << "I should be blue, I like sk" << 8 << "ting" << RESET << std::endl;
  ColorCout(CYAN) << "I should be cyan, I like tr" << 3 << "s" << RESET << std::endl;
}
