#include <iostream>
#include <utility>
#include "never.h"

using namespace std;


Never generate_it(int x, ContA<int> pass) {
never(
  pass(move(x))
)

Never double_it(int x, ContA<int> pass) {
never(
  pass(x * 2)
)

Never print_it(int x, ContV pass) {
  cout << x << endl;
never(
  pass()
)

Never start(int argc, char *argv[], ContA<int> pass) {
never(
  pipe(
    generate_it,
    double_it,
    print_it,
  )(42, feed(pass, 0))
)
