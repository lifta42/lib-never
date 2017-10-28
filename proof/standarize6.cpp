// I prefer version 7, but this is also awesome.
// note: -std=c++1z
#include <functional>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

template <typename T> using Func = function<T>;
// Expect
template <typename T> using Epct = Func<void(T &&)>;
// Standard Procedure, T -> U
template <typename T, typename U> using Proc = Func<void(T &&, Epct<U>)>;

template <typename... Ts> using PartGen = Func<void(Ts...)>;
// General Procedure, Us... -> T
template <typename T, typename... Us>
using GenProc = Func<void(Epct<T>, Epct<PartGen<Us...>>)>;

template <typename... Ts> struct NestProc;
template <typename T, typename U> struct NestProc<T, U> {
  using Type = Proc<T, U>;
};
template <typename T, typename... Us> struct NestProc<T, Us...> {
  using Type = Proc<T, typename NestProc<Us...>::Type>;
};
template <typename... Ts> using NProc = typename NestProc<Ts...>::Type;

template <typename T>
struct RevGenProc : public RevGenProc<decltype(&T::operator())> {};
template <typename T, typename... Us, typename C>
struct RevGenProc<void (C::*)(Epct<T>, Epct<PartGen<Us...>>) const> {
  using RetType = T;
  template <template <typename...> class V> using ArgType = V<Us...>;
  using ProcType = typename NestProc<Us..., T>::Type;
};

template <typename T>
struct RevProc : public RevProc<decltype(&T::operator())> {};
template <typename T, typename U, typename C>
struct RevProc<void (C::*)(T &&, Epct<U>) const> {
  using ArgType = T;
  using RetType = U;
};

template <typename T>
struct RevEpct : public RevEpct<decltype(&T::operator())> {};
template <typename T, typename C> struct RevEpct<void (C::*)(T &&) const> {
  using Type = T;
};

template <typename... Ts> struct Args;
template <typename T> struct Args<T> {
  const static bool atom;
  using Head = T;
  template <template <typename...> class U> using Tail = U<>;
};
template <typename T> const bool Args<T>::atom = true;

template <typename T, typename... Us> struct Args<T, Us...> {
  const static bool atom;
  using Head = T;
  template <template <typename...> class V> using Tail = V<Us...>;
};
template <typename T, typename... Us> const bool Args<T, Us...>::atom = false;

template <typename GP> constexpr auto stand(GP &&gp) {
  using Ts = typename RevGenProc<GP>::template ArgType<Args>;
  using U = typename RevGenProc<GP>::RetType;

  if constexpr (Ts::atom) {
    // gp :: V -> U
    // gp :: void (Epct<U>, Epct<PartGen<V>>)
    // gp :: void (Epct<U>, Epct<Func<void (V &&)>>)
    using V = typename Ts::Head;
    return [&](V &&v, Epct<U> pass) {
      gp(pass, [&](PartGen<V> &&func) { func(move(v)); });
    };
  } else {
    using V = typename Ts::Head;
    using Ws =
        typename Ts::template Tail<Args>; // not used, but keep for `ws` below
    using X = typename Ts::template Tail<PartGen>;
    using Y = typename RevGenProc<GP>::ProcType;
    using Z = typename RevProc<Y>::RetType;
    // gp :: ~Ts... -> U
    // gp :: V -> ~Ws... -> U
    // Step 1, build a GenProc which is ~Ws... -> U
    // Step 2, use `stand` to turn it into standard shape
    // Step 3, prefix the passing of argument v and return it

    // step 3
    return [&](V &&v, Epct<Z> pass) {
      // step 1
      // tail_gen_proc :: Ws... -> U
      // tail_gen_proc :: void (Epct<U>, Epct<PartGen<~Ws...>>)
      // tail_gen_proc :: void (Epct<U>, Epct<X>)
      auto tail_gen_proc = [&](Epct<U> pass, Epct<X> intern_pass) {
        intern_pass([&](auto &&... ws) {
          gp(pass, [&](auto &&func) { func(move(v), move(ws)...); });
        });
      };
      // step 2
      pass(stand(move(tail_gen_proc)));
    };
  }
}

template <typename... Ts> struct Last;
template <typename T> struct Last<T> { using Type = T; };
template <typename T, typename... Us> struct Last<T, Us...> {
  using Type = typename Last<Us...>::Type;
};

template <typename P1, typename P2>
constexpr auto pipe(P1 &&proc1, P2 &&proc2) {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<P2>::RetType;
  static_assert(is_same<typename RevProc<P2>::ArgType, U>::value,
                "Mismatch procedure type.");

  return [&](Epct<Proc<T, V>> pass) {
    pass([&](T &&t, Epct<V> pass) {
      proc1(move(t), [&](U &&u) { proc2(move(u), pass); });
    });
  };
}

template <typename P1, typename... Ps>
constexpr auto pipe(P1 &&proc1, Ps &&... procs) {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<typename Last<Ps...>::Type>::RetType;
  return [&](Epct<Proc<T, V>> &&pass) {
    pipe(move(procs)...)([&](Proc<U, V> &&proc2) {
      pipe(move(proc1), move(proc2))(move(pass));
    });
  };
}

template <typename T, typename C> constexpr auto feed(T &&fed, C pass) {
  using U = typename RevEpct<C>::Type;
  return [&](Proc<T, U> &&proc) { proc(move(fed), pass); };
}

// not used, but may be useful
template <typename T>
struct RevPartGen : public RevPartGen<decltype(&T::operator())> {};
template <typename... Ts, typename C>
struct RevPartGen<void (C::*)(Ts...) const> {
  template <template <typename...> typename U> using Type = U<Ts...>;
};

int main() {
  pipe(
      [](int &&x, Epct<NProc<int, int, int>> pass) {
        pass(stand([&](Epct<int> pass, Epct<PartGen<int, int>> intern_pass) {
          intern_pass([&](int &&y, int &&z) { pass(y + z - x); });
        }));
      },
      [](NProc<int, int, int> &&add_y_z_then_sub_x, Epct<Proc<int, int>> pass) {
        add_y_z_then_sub_x(20, pass);
      },
      [](Proc<int, int> &&add_20_z_then_sub_x, Epct<int> pass) {
        add_20_z_then_sub_x(30, pass);
      })(feed(42, [](int &&eight) { cout << eight << endl; }));
}
