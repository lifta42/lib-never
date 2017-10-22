// cps-library/src/testcase.h
// A micro framework for unit testing.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARY_TESTCASE_H
#define CPS_LIBRARY_TESTCASE_H

#include <map>
#include "function.h"


using Say = FuncA<bool>;
using Test = FuncA<Say>;
Never test(const char *case_name, const char *test_name, Test test,
  ContA<bool> pass);

using Tests = std::map<const char *, Test>;
enum Strategy { IGNORE, STOP };
Never test_testcase(const char *case_name, Strategy strategy, Tests tests,
  ContA<bool> pass);

#endif
