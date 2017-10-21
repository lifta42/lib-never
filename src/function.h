// cps-library/src/function.h
// The definations of functions.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARY_FUNCTION_H
#define CPS_LIBRARY_FUNCTION_H

#include <functional>

#define never(calling) calling }
using Never = void;

template <typename T> using Func = std::function<T>;
template <typename T> using FuncA = Func<void (T)>;
template <typename T> using FuncR = Func<T ()>;
using FuncV = FuncR<void>;

template <typename T> using ContA = Func<Never (T)>;
using ContV = Func<void ()>;

Never done();

#define Start(cont) Never start(ContA<int> cont)

#endif
