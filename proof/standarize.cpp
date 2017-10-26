#include <iostream>
#include <utility>
#include <type_traits>
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

template <typename P1, typename P2> constexpr auto pipe(P1 &&proc1, P2 &&proc2)
  -> Proc<typename RevProc<P1>::ArgType, typename RevProc<P2>::RetType> {
  using T = typename RevProc<P1>::ArgType;
  using U = typename RevProc<P1>::RetType;
  using V = typename RevProc<P2>::RetType;
  static_assert(is_same<typename RevProc<P2>::ArgType, U>::value,
    "Mismatch procedure type.");
  return [&proc1, proc2] (T &&t, Cont<V> pass) {
    proc1(move(t), [proc2, pass] (U &&u) {
      proc2(move(u), [pass] (V &&v) {
        pass(move(v));
      });
    });
  };
}
template <typename P1, typename... Ps> constexpr auto pipe(P1 &&proc1, Ps &&...procs)
  -> Proc<typename RevProc<P1>::ArgType, typename RevProc<decltype(pipe(move(procs)...))>::RetType> {
  return pipe(move(proc1), pipe(move(procs)...));
}

int main() {
  Func<void ()> var1;
  Cont<int> var2([] (int &&x) {});
  Proc<int, int> var3([] (int &&x, Cont<int> pass) {
    pass(x + 1);
  });
  auto var4 = pipe(move(var3), move(var3));
  var4(42, [] (int &&x) {
    cout << x << endl;
  });
  Proc<string, int> var5([] (string &&str, Cont<int> pass) {
    pass(str.length());
  });
  // auto var6 = pipe(var5, var5);
  Proc<int, int> var7 = pipe(move(var3), move(var3), move(var3));
  var7(42, [] (int &&x) {
    cout << x << endl;
  });
  auto var8 = pipe(move(var5), move(var3), move(var3));
  var8("something", [] (int &&x) {
    cout << x << endl;
  });

  return 0;
}
