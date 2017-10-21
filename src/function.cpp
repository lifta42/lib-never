#include "function.h"

Never done() {
  //
}

extern Never start(ContA<int> cont);
int main() {
  int returned_code = 0;
  start([&] (int &&result) {
    returned_code = result;
  });
  return returned_code;
}
