// cps-library/source/nolambda.h
// Some helper to avoid writing lambda explicitly.
// 2017.10.24 by liftA42.
#ifndef CPS_LIBRARY_NOLAMBDA_H
#define CPS_LIBRARY_NOLAMBDA_H

#include "function.h"

template <typename T> ContV feed(ContA<T> cont, T &&value);

template <typename T, typename U, typename V> Func<Never (T &&, ContA<V>)> pipe(
  Func<Never (T &&, ContA<U>)> func1, Func<Never (U &&, ContA<V>)> func2);

#endif
