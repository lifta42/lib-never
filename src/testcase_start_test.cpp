#include "testcase_start.h"


TESTCASE(TestcaseStart, STOP, (Tests {
  {"simple test 1", [] (Say say) {
    say(2 * 512 == 4 * 256);
  }},
  {"simple test 2", [] (Say say) {
    say(4 * 256 == 8 * 128);
  }}
}))

unsigned color(int red, int green, int blue, float alpha) {
  return (red & 0xff) << 24 | (green & 0xff) << 16 | (blue & 0xff) << 8 |
    (int(alpha * 255) & 0xff);
}

TESTCASE(MoreTestcase, STOP, (Tests {
  {"a red test", [] (Say say) {
    say(color(255, 0, 0, 1) == 0xff0000ff);
  }},
  {"a blue test", [] (Say say) {
    say(color(0, 0, 255, 1) == 0x0000fffe);
  }},
  {"a green (unreachable test)", [] (Say say) {
    say(color(0, 255, 0, 1) == 0x00ff00ff);
  }}
}))

TESTCASE(MoreColor, IGNORE, (Tests {
  {"an yellow test", [] (Say say) {
    say(color(255, 255, 0, 1) == 0xfffe00ff);
  }},
  {"a purple test", [] (Say say) {
    say(color(255, 0, 255, 1) == 0xff00ffff);
  }}
}))
