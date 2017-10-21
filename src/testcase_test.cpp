#include "testcase.h"
#include "function.h"
#include <iostream>
using namespace std;

Never test_assert(ContV cont) {
never(
  test("assert true expression", [] (Say say) {
    say(2 < 3);
  }, [&] (bool _) {
  never(
    test("assert false expression", [] (Say say) {
      say(2 > 3);
      // never reachable
      throw "should not be executed";
    }, [&] (bool _) {
    never(
        cont();
    ));
  ));
)

Start(ret) {
never(
  test_assert([&] () {
    ret(0);
  });
)
