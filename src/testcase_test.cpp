#include "testcase.h"
#include "function.h"


Never test_test(ContV pass) {
never(
  test("testcase name", "test name", [] (Say say) {
    say(true);
    say(false);
    say(true);  // unreachable
  }, [&] (bool ok) {
  never(
    pass()
  ))
)


Never start(int argc, char *argv[], ContA<int> pass) {
never(
  test_test([&] () {
  never(
    pass(0)
  ))
)
