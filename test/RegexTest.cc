#include <memory>

#include <gtest/gtest.h>
#include <boost/filesystem.hpp>
#include <string_view>

#include "Match/Engine.h"

namespace fs = boost::filesystem;

TEST(Regex, Find) {
  std::string_view sv = "foobarfoocfoo";
  size_t end = sv.size();
  Engine engine("foo[bc]");

  size_t match1 = engine.Find(sv, 0, end);
  ASSERT_EQ(match1, 0);

  size_t match2 = engine.Find(sv, match1 + 1, end);
  ASSERT_EQ(match2, 6);
}

/*
 * match a pattern against a directory
 */
TEST(Regex, MatchAll) {
  std::cout << fs::initial_path() << std::endl;
  fs::path path = "test/A_Pale_View_of_Hills.txt";
  std::string patrn = "^As far as.*a fortnight or so later.$";
  Engine engine(patrn);
  std::unique_ptr<Result> result = engine.MatchAll(path);
  std::ostringstream oss;
  oss << *result;
  std::string result_str = oss.str();
  ASSERT_STREQ(result_str.c_str(), "220: As far as I remember, that was all that took place between us that morning. I had no wish to alarm the child further, and before long I turned and made my way back across the wasteground. The child\xE2\x80\x99s response had, it is true, upset me somewhat; for in those days, such small things were capable of arousing in me every kind of misgiving about motherhood. I told myself the episode was insignificant, and that in any case, further opportunities to make friends with the little girl were bound to present themselves over the coming days. As it was, I did not speak to Mariko again until one afternoon a fortnight or so later.: 0\n\n");
}
