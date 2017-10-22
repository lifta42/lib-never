#include "control.h"
#include "testcase.h"
#include "function.h"


TestcaseStart("Control", true, (Tests {
  Test("when select true branch", {
  never(
    when(Expr(2 < 3),
      [&] () {
        say(true);
      }, [&] () {
        say(false);
      }
    );
  )),
  Test("when select false branch", {
    // int x = 2, y = 3;
  never(
    when(Expr(2 > 3),
      [&] () {
        say(false);
      }, [&] () {
        say(true);
      }
    );
  ))
}))
