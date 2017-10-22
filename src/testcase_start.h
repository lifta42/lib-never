// cps-library/src/testcase_start.h
// A global manager and entry point for testcases.
// 2017.10.22 by liftA42.
#ifndef CPS_LIBRARY_TESTCASE_START_H
#define CPS_LIBRARY_TESTCASE_START_H

#include "testcase.h"


using DummyType = int;
DummyType store_testcase(const char *case_name, Strategy strategy, Tests tests);

#define TESTCASE(case_name, strategy, tests) \
  DummyType never_dummy_var_for_##case_name = \
    store_testcase(#case_name, strategy, tests);

#endif
