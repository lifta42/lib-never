#define NEVER_TESTCASE
#include "../never.h"


TESTCASE(NoLambdaTest, STOP,
  TEST(simple_feed, SAY(say) {
    feed(ContA<int>([&] (int &&x) -> Never {
      say(x == 42);
    never(
      // ?
    )), 42)();
  })
)
