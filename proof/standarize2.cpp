#include <iostream>
#include <utility>
#include <string>

using namespace std;


template <typename T> using Func = std::function<T>;
template <typename T> using Cont = Func<void (T &&)>;
template <typename T, typename U> using Proc = Func<Cont<Cont<U>> (T &&)>;

template <typename T> struct RevProc;
template <typename T, typename U> struct RevProc<Proc<T, U>> {
  using ArgType = T;
  using RetType = U;
};

template <typename P1, typename P2> constexpr auto pipe(P1 &&proc1, P2 &&proc2)
  -> Proc<typename RevProc<P1>::ArgType, typename RevProc<P2>::RetType> {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<P2>::RetType;
  static_assert(is_same<typename RevProc<P2>::ArgType, U>::value,
    "Mismatch procedure type.");

  return [&proc1, &proc2] (T &&t) {
    return [&proc1, &proc2, &t] (Cont<V> &&pass) {
      return proc1(move(t))([&proc2, &pass] (U &&u) {
        proc2(move(u))(move(pass));
      });
    };
  };
}
template <typename P1, typename... Ps> constexpr auto pipe(P1 &&proc1, Ps &&...procs)
  -> Proc<typename RevProc<P1>::ArgType, typename RevProc<decltype(pipe(move(procs)...))>::RetType> {
  return pipe(move(proc1), pipe(move(procs)...));
}

int main() {
  Proc<int, int> var1([] (int &&x) {
    return [&x] (Cont<int> &&pass) {
      pass(x + 1);
    };
  });
  var1(42)([] (int &&x) {
    cout << x << endl;
  });

  Proc<int, int> var2 = pipe(move(var1), move(var1));
  var2(42)([] (int &&x) {
    cout << x << endl;
  });

  Proc<int, int> var3 = pipe(move(var1), pipe(move(var1), move(var1)));
  var3(42)([] (int &&x) {
    cout << x << endl;
  });

  Proc<int, int> var4 = pipe(move(var1), move(var1), move(var1));
  // var4(42)([] (int &&x) {
  //   cout << x << endl;
  // });
}
