#include <iostream>
#include <utility>
#include <string>

using namespace std;


template <typename T> using Func = std::function<T>;
template <typename T> using Cont = Func<void (T &&)>;
template <typename T, typename U> using Proc = Func<void (T &&, Cont<U>)>;

template <typename T> struct RevProc;
template <typename T, typename U> struct RevProc<Proc<T, U>> {
  using ArgType = T;
  using RetType = U;
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
  Ps &&...procs) -> Cont<Cont<
    Proc<typename RevProc<P1>::ArgType,
      typename RevProc<typename Last<Ps...>::Type>::RetType>>> {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<typename Last<Ps...>::Type>::RetType;
  return [&] (Cont<Proc<T, V>> &&pass) {
    pipe(move(procs)...)([&] (Proc<U, V> &&proc2) {
      pipe(move(proc1), move(proc2))(move(pass));
    });
  };
}

int main() {
  Proc<int, int> var1([] (int &&x, Cont<int> pass) {
    pass(x + 1);
  });
  var1(42, [&] (int &&x) {
    cout << x << endl;

    pipe(move(var1), move(var1))([&] (Proc<int, int> &&var2) {
      var2(42, [&] (int &&x) {
        cout << x << endl;

        pipe(move(var1), move(var1), move(var1))([&] (Proc<int, int> &&var3) {
          var3(42, [&] (int &&x) {
            cout << x << endl;

            pipe(Proc<string, string>([] (string &&prefix, Cont<string> pass) {
              pass(prefix + "hello ");
            }), Proc<string, string>([] (string &&hello, Cont<string> pass) {
              pass(hello + "world");
            }), Proc<string, string>([] (string &&hello_world, Cont<string> pass) {
              pass(hello_world + "!");
            }))([] (Proc<string, string> &&append_hello_world) {
              append_hello_world("Cowsay said, ", [] (string &&str) {
                cout << str << endl;
              });
            });
          });
        });
      });
    });
  });
}
