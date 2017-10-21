// cps-library/src/control.h
// Some controlling flow like `if`, `while` and `for`.
// 2017.10.20 by liftA42.
#ifndef CPS_LIBRARI_CONTROL_H
#define CPS_LIBRARI_CONTROL_H

#include <functional>

#define never(calling) calling }
typedef void Never;

template <typename T> using Func = std::function<T>;
template <typename T> using FuncA = Func<Never (T)>;
using FuncV = Func<Never ()>;
template <typename T> using ContA = FuncA<T>;
using ContV = FuncV;
template <typename T> using FuncR = Func<T ()>;

Never done();

// if
Never when(FuncR<bool> &&condition, ContV &&true_cont, ContV &&false_cont);

#endif
