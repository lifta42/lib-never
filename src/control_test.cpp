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
  }, [&] () {
    cout << false_string << endl;
  });
)

int main() {
  test_when(done);
  return 0;
}
