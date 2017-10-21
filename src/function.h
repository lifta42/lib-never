// cps-library/src/function.h
// The definations of functions.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARI_FUNCTION_H
#define CPS_LIBRARI_FUNCTION_H

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

#endif
