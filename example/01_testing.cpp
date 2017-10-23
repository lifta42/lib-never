#define NEVER_TESTCASE
#include "never.h"


TESTCASE(SimpleTest, IGNORE, (Tests {
  {"test 1", TEST(say) {
    say(21 * 2 == 42);
  }},
  {"test 2", TEST(say) {
    say(21 * 2 != 42);
  }},
  {"test 3", TEST(say) {
    say(21 * 2 == 40 + 2);
    say(40 + 2 == 21 * 2);
  }}
}))
