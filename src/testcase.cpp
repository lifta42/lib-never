#include <iostream>
#include "testcase.h"


Never test(const char *desc, Test block, ContA<bool> cont) {
  std::cout << "testing " << desc << "...";
  block([&cont] (bool asserted) {
    // should not depend on anything in this module
    // so do not use functions from `control`
    asserted || \
      std::cout << "FAILED" << std::endl && \
      // trivial `, true` for boolean expr
      // todo: hard question, this callback may return and may not
      (cont(false), true);
  });
  std::cout << "ok" << std::endl;
never(
  cont(true);
)

ContA<ContA<bool>> test_c(const char *desc, Test block) {
  return [&desc, &block] (ContA<bool> cont) {
  never(
    test(desc, block, cont);
  );
}

Never testcase(const char *desc, std::map<const char *, Test> &&tests,
  ContV &&cont) {

}
