#define NEVER_TESTCASE
#include "never.h"


TESTCASE(SimpleTest, IGNORE,
  TEST(test_1, WITH(say, done) {
    say(21 * 2 == 42);
  never(
    done()
  )),
  TEST(test_2, WITH(say, done) {
    say(21 * 2 != 42);
  never(
    done()
  )),
  TEST(test_3, SAY(say, done) {
    say(21 * 2 == 40 + 2);
    say(40 + 2 == 21 * 2);
  never(
    done()
  ))
)
