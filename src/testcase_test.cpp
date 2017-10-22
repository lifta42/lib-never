#include "testcase.h"
#include "function.h"


Never test_test(ContV pass) {
never(
  test("testcase name", "test name", [] (Say say) {
    say(true);
  }, [&] (bool ok) {
  never(
    pass()
  ))
)


Never start(int argc, char *argv[], ContA<int> pass) {
never(
  pass(0)
)
