#include <map>
#include <iostream>
#include "testcase_start.h"
#include "function.h"

using Testcases = std::map<const char *, Tests>;
Testcases &testcases() {
  static Testcases testcases;
  return testcases;
}

DummyType store_testcase(const char *name, Tests tests) {
  testcases()[name] = tests;
  return DummyType(42);
}

Never test_all(Testcases &testcases, ContA<bool> pass) {
  using namespace std;

never(
  if (testcases.size() == 0) {
  never(
    pass(true)
  )
  else {
    Testcases::iterator first_testcase = testcases.begin();
    const char *testcase_name = first_testcase->first;
    Tests testcase_body = first_testcase->second;
    testcases.erase(first_testcase);
    cout << ">> start testcase " << testcase_name << endl;
  never(
    test_testcase(testcase_name, IGNORE, testcase_body,
      [testcase_name, &testcases, &pass] (bool ok) {
      cout << ">> finish testcase " << testcase_name << endl;
    never(
      test_all(testcases, ok ? pass : [&pass] (bool _) {
      never(
        pass(false)
      ))
    ))
  )
)

Never start(int argc, char *argv[], ContA<int> pass) {
never(
  test_all(testcases(), [&pass] (bool ok) {
  never(
    pass(ok ? 0 : 1)
  ))
)
