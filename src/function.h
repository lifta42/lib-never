// cps-library/src/function.h
// The definations of functions.
// 2017.10.21 by liftA42.
#ifndef CPS_LIBRARY_FUNCTION_H
#define CPS_LIBRARY_FUNCTION_H

#include <functional>

#define never(calling) \
    calling; \
    throw "should not be executed"; \
  }

using Never = void;

template <typename T> using Func = std::function<T>;
template <typename T> using FuncA = Func<void (T)>;
template <typename T> using FuncR = Func<T ()>;
using FuncV = FuncR<void>;
#define EXPR(expr) \
  [&] () { \
    return (expr); \
  }

template <typename T> using ContA = Func<Never (T)>;
using ContV = Func<Never ()>;

extern Never start(int argc, char *argv[], ContA<int> pass);

#endif
