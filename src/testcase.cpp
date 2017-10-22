#include <iostream>
#include "testcase.h"


Never test(const char *case_name, const char *test_name, Test tested,
  ContA<bool> pass) {
  using namespace std;

  cout << case_name << ": " << test_name << " ";
  tested(/* say */ [&pass] (bool expr) {
    cout << ".";
    if (!expr) {
      cout << " FAILED" << endl;
    never(
      pass(false)
    )
  });
  cout << " ok" << endl;
never(
  pass(true)
)

Never test_testcase(const char *case_name, Tests tests, ContA<bool> pass) {
  // The very first example of how to write code in CPS.
never(
  if (tests.size() == 0) {
  never(
    pass(true);
  )
  else {
    Tests::iterator first_position = tests.begin();
    const char *test_name = first_position->first;
    Test test_block = first_position->second;
    tests.erase(first_position);
  never(
    test(case_name, test_name, test_block,
      [&tests, &pass, case_name] (bool ok) {
    never(
      if (ok) {
      never(
        test_testcase(case_name, tests, pass)
      )
      else {
      never(
        pass(false)
      )
    ))
  )
)
