// cps-library/src/testcase.h
// A micro framework for unit testing.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARY_TESTCASE_H
#define CPS_LIBRARY_TESTCASE_H

#include <list>
#include "function.h"

using Say = FuncA<bool>;
using Test = FuncA<Say>;
Never test(const char *description, Test block, ContA<bool> cont);

using CurryTest = ContA<ContA<bool>>;
CurryTest test_c(const char *description, Test block);

Never testcase(const char *desc, bool ignore, std::list<CurryTest> tests,
  ContV cont);

#endif
