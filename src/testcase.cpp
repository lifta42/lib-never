#include <iostream>
#include "testcase.h"


Never test(const char *desc, Test block, ContA<bool> cont) {
  std::cout << "testing " << desc << " ";
  block([&cont] (bool asserted) {  // say
    std::cout << ".";
    // should not depend on anything in this module
    // so do not use functions from `control`
    asserted || \
      std::cout << " FAILED" << std::endl && \
      // trivial `, true` for boolean expr
      // todo: hard question, this callback may return and may not
      // so should `say` be a `FuncA` or a `ContA`
      (cont(false), true);
  });
  std::cout << " ok" << std::endl;
never(
  cont(true);
)

CurryTest test_c(const char *desc, Test block) {
  return [desc, &block] (ContA<bool> cont) {
  never(
    test(desc, block, cont);
  );
}

Never testcase(const char *desc, bool ignore, std::list<CurryTest> tests,
  ContV cont) {
  // should not depend on control module, so do not use control method
  if (tests.size() == 0) {
  never(
    cont();
  )
  else {
    CurryTest test = tests.front();
    tests.pop_front();
    std::cout << desc << ": ";
  never(
    test([&ignore, desc, &tests, &cont] (bool passed) {
    never(
      if (!passed && !ignore) {
      never(
        cont();
      )
      else {
      never(
        testcase(desc, ignore, tests, cont);
      )
    ));
  )
}
