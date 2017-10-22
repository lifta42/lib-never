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

Never test_test_testcase(ContV pass) {
never(
  test_testcase("simple testcase", {
    {"test 1", [] (Say say) {
      say(2 < 3);
      say(3 < 4);
    }},
    {"test 2", [] (Say say) {
      say(5 == 5);
      say(6 == 7);
      say(7 == 7);
    }},
    {"unreachable test", [] (Say say) {
      say(true);
    }}
  }, [&] (bool ok) {
  never(
    pass()
  ))
)

Never start(int argc, char *argv[], ContA<int> pass) {
never(
  test_test([&] () {
  never(
    test_test_testcase([&] () {
    never(
      pass(0)
    ))
  ))
)
