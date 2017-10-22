#include <map>
#include <iostream>
#include "testcase_start.h"
#include "function.h"

using Testcases = std::map<const char *, Tests>;
using TestcaseFlag = std::map<const char *, Strategy>;
Testcases &testcases() {
  static Testcases testcases;
  return testcases;
}
TestcaseFlag &flags() {
  static TestcaseFlag flags;
  return flags;
}

DummyType store_testcase(const char *name, Strategy strategy, Tests tests) {
  testcases()[name] = tests;
  flags()[name] = strategy;
  return DummyType(42);
}

Never test_all(Testcases &testcases, TestcaseFlag &flags, ContA<bool> pass) {
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
    test_testcase(testcase_name, flags[testcase_name], testcase_body,
      [testcase_name, &testcases, &flags, &pass] (bool ok) {
      cout << ">> finish testcase " << testcase_name << endl;
    never(
      test_all(testcases, flags, ok ? pass : [&pass] (bool _) {
      never(
        pass(false)
      ))
    ))
  )
)

Never start(int argc, char *argv[], ContA<int> pass) {
never(
  test_all(testcases(), flags(), [&pass] (bool ok) {
  never(
    pass(ok ? 0 : 1)
  ))
)
