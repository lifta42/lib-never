#include "testcase.h"


TestcaseStart("simple testcase", true, (Tests {
  Test("fail asserting", {
    say(2 > 3);
  }),
  Test("passed asserting", {
    say(2 < 3);
    say(3 < 4);
  })
}))
