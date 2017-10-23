#define NEVER_TESTCASE
#include "never.h"


TESTCASE(SimpleTest, IGNORE,
  TEST(test_1, SAY(say) {
    say(21 * 2 == 42);
  }),
  TEST(test_2, SAY(say) {
    say(21 * 2 != 42);
  }),
  TEST(test_3, SAY(say) {
    say(21 * 2 == 40 + 2);
    say(40 + 2 == 21 * 2);
  })
)
