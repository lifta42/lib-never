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
