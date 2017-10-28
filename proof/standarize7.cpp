#include <iostream>
#include <string>
#include <utility>
#include <functional>

using namespace std;


template <typename T> using Func = std::function<T>;
using Never = void;
template <typename T> using Cont = Func<Never (T &&)>;
template <typename T, typename U> using Proc = Func<Never (T &&, Cont<U>)>;

template <typename... Ts> struct _Last;
template <typename T> struct _Last<T> {
  using Type = T;
};
template <typename T, typename... Us> struct _Last<T, Us...> {
  using Type = typename _Last<Us...>::Type;
};
template <typename... Ts> using Last = typename _Last<Ts...>::Type;

template <typename... Ts> struct Init;
template <typename T, typename U> struct Init<T, U> {
  template <template <typename...> class V> using Type = V<T>;
};
template <typename T, typename... Us> struct Init<T, Us...> {
  template <template <typename...> class W> using T1 = typename Init<Us...>::template Type<W>; // T1: W<...>
  template <typename... Ts> struct Foo {
    template <template <typename...> class W> using T2 = W<T, Ts...>;
  };
  template <template <typename...> class V> using Type = typename T1<Foo>::template T2<V>;
};

// Proc<T1, Proc<T2, ... , Proc<Tn, U>...>>  <~>  GenProc<T1, T2, ... , Tn, U>
//                                           ===  NestedProc<T1, T2, ... , Tn, U>
template <typename... Ts> struct _GenProc {
  template <typename... Us> struct Foo {
    using RetType = Last<Ts...>;
    using Type = Func<Never (Us &&..., Cont<RetType>)>;
  };
  using Type = typename Init<Ts...>::template Type<Foo>::Type;
};
template <typename... Ts> using GenProc = typename _GenProc<Ts...>::Type;

template <typename T> struct ContTrait : public ContTrait<decltype(&T::operator())> {};
template <typename T, typename C> struct ContTrait<Never (C::*)(T &&) const> {
  using Type = T;
};

template <typename T> struct ProcTrait : public ProcTrait<decltype(&T::operator())> {};
template <typename T, typename U, typename C> struct ProcTrait<Never (C::*)(T &&, Cont<U>) const> {
  using ArgType = T;
  using RetType = U;
};

template <typename T> struct GenProcTrait : public GenProcTrait<decltype(&T::operator())> {};
template <typename T, typename U, typename C> struct GenProcTrait<Never (C::*)(T &&, Cont<U>) const> {
  template <template <typename...> class V> using ArgType = V<T>;
  using RetType = U;
  using NestedType = Proc<T, U>;
};
template <typename T, typename... Us, typename C> struct GenProcTrait<Never (C::*)(T &&, Us...) const> {
  template <typename... Ts> struct Bar;
  template <typename... Ts> struct Bar<Ts &&...> {
    template <template <typename...> class V> using Type = V<Ts..., typename ContTrait<Last<Us...>>::Type>;
  };
  using TailProc = typename Init<Us...>::template Type<Bar>::template Type<GenProc>;
  template <typename... Ts> struct Foo {
    template <template <typename...> class V> using Type = V<T, Ts...>;
  };
  template <template <typename...> class V> using ArgType = typename GenProcTrait<TailProc>::template ArgType<Foo>::template Type<V>;
  using RetType = typename GenProcTrait<TailProc>::RetType;
  using NestedType = Proc<T, typename GenProcTrait<TailProc>::NestedType>;
};
template <typename GP> using NestedProc = typename GenProcTrait<GP>::NestedType;
template <typename... Ts> using Nested = typename GenProcTrait<GenProc<Ts...>>::NestedType;

template <typename... Ts> struct StandFoo {};
template <typename T> struct StandFoo<T> {
  const static bool flag;
  using Type = T;
};
template <typename T> const bool StandFoo<T>::flag = true;
template <typename T, typename... Us> struct StandFoo<T, Us...> {
  const static bool flag;
  using Type = T;
  template <typename R> using BarType = GenProc<Us..., R>;
};
template <typename T, typename... Us> const bool StandFoo<T, Us...>::flag = false;
template <typename GP> using SingleArg = typename GenProcTrait<GP>::template ArgType<StandFoo>;

template <typename GP> auto stand_impl(GP &&gp, Cont<NestedProc<GP>> pass)
  -> enable_if_t<SingleArg<GP>::flag> {
  using R = typename GenProcTrait<GP>::RetType;
  using T = typename GenProcTrait<GP>::template ArgType<StandFoo>::Type;
  pass([&] (T &&t, Cont<R> pass) {
    gp(move(t), pass);
  });
}

template <typename... Ts> struct StandBar {
  template <typename U, typename V, typename R, typename W>
  auto bar(U &&u, V &&gp, Cont<W> pass) {
    pass([&] (Ts &&...ts, Cont<R> pass) {
      gp(move(u), move(ts)..., pass);
    });
  }
};


template <typename GP> auto stand_impl(GP &&gp, Cont<NestedProc<GP>> pass)
  -> enable_if_t<!SingleArg<GP>::flag> {
  // GP :: GenProc<int, int, int>
  // U  :: GenProc<int, int>
  // V  :: Proc<int, int>
  using R = typename GenProcTrait<GP>::RetType;
  using T = typename GenProcTrait<GP>::template ArgType<StandFoo>::Type;
  using U = typename GenProcTrait<GP>::TailProc;
  using V = NestedProc<U>;
  using W = typename GenProcTrait<GP>::template ArgType<StandFoo>::template BarType<R>;
  pass([&] (T &&t, Cont<V> pass) {
    using X = typename GenProcTrait<U>::template ArgType<StandBar>;
    X stdbar;
    stdbar.template bar<T, GP, R, W>(move(t), move(gp), [&] (W &&tail_gen_proc) {
      // pass :: Cont<Proc<int, int>>
      // tail_gen_proc :: GenProc<int, int>
      stand_impl(move(tail_gen_proc), pass);
    });
  });
}

template <typename GP> auto stand(GP &&gp, Cont<NestedProc<GP>> pass) {
  stand_impl(move(gp), pass);
}

int main() {
  stand([] (int &&x, int &&y, Cont<int> pass) {
    pass(x + y);
  }, [] (auto &&proc) {
    proc(3, [] (auto &&proc) {
      proc(5, [] (int &&eight) {
        cout << eight << endl;
      });
    });
  });
}
