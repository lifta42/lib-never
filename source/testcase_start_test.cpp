#include "testcase_start.h"


TESTCASE(TestcaseStart, STOP,
  TEST(simple_test_1, SAY(say) {
    say(2 * 512 == 4 * 256);
  }),
  TEST(simple_test_2, SAY(say) {
    say(4 * 256 == 8 * 128);
  })
)

unsigned color(int red, int green, int blue, float alpha) {
  return (red & 0xff) << 24 | (green & 0xff) << 16 | (blue & 0xff) << 8 |
    (int(alpha * 255) & 0xff);
}

TESTCASE(MoreTestcase, STOP,
  TEST(a_red_test, SAY(say) {
    say(color(255, 0, 0, 1) == 0xff0000ff);
  }),
  TEST(a_blue_test, SAY(say) {
    say(color(0, 0, 255, 1) == 0x0000fffe);
  }),
  TEST(a_green_unreachable_test, SAY(say) {
    say(color(0, 255, 0, 1) == 0x00ff00ff);
  })
)

TESTCASE(MoreColor, IGNORE,
  TEST(a_yellow_test, SAY(say) {
    say(color(255, 255, 0, 1) == 0xfffe00ff);
  }),
  TEST(a_purple_test, SAY(say) {
    say(color(255, 0, 255, 1) == 0xff00ffff);
  })
)
