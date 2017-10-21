// cps-library/src/control.h
// Some controlling flow like `if`, `while` and `for`.
// 2017.10.20 by liftA42.
#ifndef CPS_LIBRARI_CONTROL_H
#define CPS_LIBRARI_CONTROL_H

#include "function.h"

// if
Never when(FuncR<bool> &&condition, ContV &&true_cont, ContV &&false_cont);

#endif
