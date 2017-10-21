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

Never test_curry(ContV cont) {
never(
  test_c("assert in a currying test function", [] (Say say) {
    int x = 42;
    say(x == 42);
  })([&] (bool _) {
  never(
    cont();
  ));
)


Start(ret) {
never(
  test_assert([&] () {
  never(
    test_curry([&] () {
    never(
      ret(0);
    ));
  ));
)
