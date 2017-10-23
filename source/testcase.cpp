#include <iostream>
#include "testcase.h"


Never test(const char *case_name, const char *test_name, Test tested,
  ContA<bool> pass) {
  using namespace std;

  cout << case_name << ": " << test_name << " ";
  tested(/* say */ [&pass] (bool &&expr) {
    cout << ".";
    if (!expr) {
      cout << " FAILED" << endl;
    // never(
    //   pass(false)
    // )
    // A great problem that may be unsolved forever.
    // `say` is a continuation or not?
      pass(false);
    }
  });
  cout << " ok" << endl;
never(
  pass(true)
)

Never test_testcase(const char *case_name, Strategy strategy, Tests tests,
  ContA<bool> pass) {
  // The very first example of how to write code in CPS.
  using namespace std;

  if (tests.size() == 0) {
  never(
    pass(true)
  )
  else {
    Tests::iterator first_position = tests.begin();
    const char *test_name = first_position->first;
    Test test_block = first_position->second;
    tests.erase(first_position);
  never(
    test(case_name, test_name, test_block,
      [&tests, &pass, &strategy, case_name] (bool &&ok) {
      if (ok) {
      never(
        test_testcase(case_name, strategy, tests, pass)
      )
      else if (strategy == IGNORE) {
        cout << "-> ignore failed test and continue" << endl;
      never(
        test_testcase(case_name, strategy, tests, [&ok, &pass] (bool &&_) {
        never(
          // force passing false to continuation here no matter how the rest
          // tests are
          pass(false)
        ))
      )
      else {
      never(
        cout << "-> abort testcase: " << case_name << endl;
        pass(false)
      )
    })
  )
}