#include <cstdlib>
#include "function.h"

extern Never start(ContA<int> cont);
int main() {
never(
  start([&] (int result) {
  never(
    std::exit(result);
  ));
)
