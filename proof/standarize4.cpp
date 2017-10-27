#include <iostream>
#include <utility>
#include <string>

using namespace std;

template <typename T> using Func = std::function<T>;
template <typename T> using Cont = Func<void (T &&)>;
template <typename T, typename U> using Proc = Func<void (T &&, Cont<U>)>;

template <typename T> struct RevProc : public RevProc<decltype(&T::operator())> {};
template <typename T, typename U, typename C> struct RevProc<void (C::*)(T &&, Cont<U>) const> {
  using ArgType = T;
  using RetType = U;
};

template <typename T> struct RevCont : public RevCont<decltype(&T::operator())> {};
template <typename T, typename C> struct RevCont<void (C::*)(T &&) const> {
  using Type = T;
};

template <typename... Ts> struct Last;
template <typename T> struct Last<T> {
  using Type = T;
};
template <typename T, typename... Us> struct Last<T, Us...> {
  using Type = typename Last<Us...>::Type;
};

template <typename P1, typename P2> constexpr auto pipe(P1 &&proc1, P2 &&proc2)
  -> Cont<Cont<
    Proc<typename RevProc<P1>::ArgType, typename RevProc<P2>::RetType>>> {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<P2>::RetType;
  static_assert(is_same<typename RevProc<P2>::ArgType, U>::value,
    "Mismatch procedure type.");

  return [&] (Cont<Proc<T, V>> pass) {
    pass([&] (T &&t, Cont<V> pass) {
      proc1(move(t), [&] (U &&u) {
        proc2(move(u), pass);
      });
    });
  };
}

template <typename P1, typename... Ps> constexpr auto pipe(P1 &&proc1,
  Ps &&...procs) {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<typename Last<Ps...>::Type>::RetType;
  return [&] (Cont<Proc<T, V>> &&pass) {
    pipe(move(procs)...)([&] (Proc<U, V> &&proc2) {
      pipe(move(proc1), move(proc2))(move(pass));
    });
  };
}

template <typename T, typename C> constexpr auto feed(T &&fed, C pass) {
  using U = typename RevCont<C>::Type;
  return [&] (Proc<T, U> &&proc) {
    proc(move(fed), pass);
  };
}

// auto standarize(Func<Func<void (int &&, int &&)> (Cont<int>)> &&no_cont_proc) {
//   return [=] (auto pass1) {
//     pass1([=] (int &&arg1, Cont<Proc<int, int>> pass2) {
//       int arg1b = arg1;
//       pass2([=] (int &&arg2, Cont<int> pass3) {
//         int arg1c = arg1b;
//         cout << "about to calling" << endl;
//         no_cont_proc(pass3)(move(arg1c), move(arg2));
//       });
//     });
//   };
// }

// #define STANDARIZE(type, pass, proc) \
//   standarize([] (Cont<type> pass) {
//     return proc;
//   })
// auto bar = STANDARIZE(int, pass, [&] (int &&x, int &&y, int &&z) {
//   pass(x + y + z);
// });

int main() {
  pipe([] (int &&x, Cont<Proc<int, Proc<int, int>>>pass) {
    pass([&] (int &&y, Cont<Proc<int, int>> pass) {
      pass([&] (int &&z, Cont<int> pass) {
        pass(move(x) + move(y) + move(z));
      });
    });
  }, [] (Proc<int, Proc<int, int>> &&add_x_y, Cont<Proc<int, int>> pass) {
    add_x_y(42, pass);
  }, [] (Proc<int, int> &&add_x, Cont<int> pass) {
    add_x(42, pass);
  }, [] (int &&res, Cont<bool> pass) {
    cout << res << endl;
    pass(true);
  })(feed(0, [] (bool &&t) {
    cout << t << endl;
    // standarize([] (Cont<int> pass) {
    //   return [&] (int &&x, int &&y) {
    //     pass(x + y);
    //   };
    // })([] (Proc<int, Proc<int, int>> &&foo) {
    //   foo(42, [] (Proc<int, int> &&proc) {
    //     proc(42, [] (int &&x) {
    //       cout << x << endl;
    //     });
    //   });
    // });
  }));
}
