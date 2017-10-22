#include "testcase.h"


TestcaseStart("TestcaseStart", true, (Tests {
  Test("fail asserting", {
    say(2 > 3);
  }),
  Test("passed asserting", {
    say(2 < 3);
    say(3 < 4);
  })
}))
