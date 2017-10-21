// cps-library/src/testcase.h
// A micro framework for unit testing.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARY_TESTCASE_H
#define CPS_LIBRARY_TESTCASE_H

#include <map>
#include "function.h"

using Say = FuncA<bool>;
using Test = FuncA<Say>;

Never test(const char *description, Test block, ContA<bool> cont);
ContA<ContA<bool>> test_c(const char *desc, Test block);

#endif
