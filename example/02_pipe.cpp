#include <iostream>
#include "never.h"

Never generate_it(int x, ContA<int> pass) {
never(
  pass(x)
)

Never double_it(int x, ContA<int> pass) {
never(
  pass(x * 2)
)

Never print_it(int x, ContV pass) {
  std::cout << x << std::endl;
never(
  pass()
)

Never start(int argc, char *argv[], ContA<int> pass) {
never(
  pipe(
    generate_it,
    double_it,
    print_it,
  )(42, [&pass] () {
  never(
    pass(0)
  ))
)
