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

Never test_testcase(ContV cont) {
never(
  testcase("ignore testcase", true, {
    test_c("simple assertion 1", [] (Say say) {
      say(2 > 3);
    }),
    test_c("simple assertion 2", [] (Say say) {
      say(3 < 4);
    })
  }, [&] () {
  never(
    testcase("break testcase", false, {
      test_c("simple assertion 1", [] (Say say) {
        say(2 > 3);
      }),
      test_c("simple assertion 2", [] (Say say) {
        say(3 < 4);
      })
    }, cont);
  ));
)



Start(ret) {
never(
  test_assert([&] () {
  never(
    test_curry([&] () {
    never(
      test_testcase([&] () {
      never(
        ret(0);
      ));
    ));
  ));
)
