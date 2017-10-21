#include <iostream>
#include "control.h"


Never test_when(ContV cont) {
  using std::cout;
  using std::endl;

  char true_string[] = "This is true branch.";
  char false_string[] = "This is false branch.";

never(
  when([] () {
    return 2 < 3;
  }, [&] () {
    cout << true_string << endl;
  never(
    cont();
  ), [&] () {
    cout << false_string << endl;
  never(
    cont();
  ));
)

Never start(ContA<int> cont) {
  using std::cout;
  using std::endl;

never(
  test_when([&] () {
    cout << "Done." << endl;
  never(
    cont(0);
  ));
)
