#include <iostream>
#include <utility>
#include <functional>
#include <string>

using namespace std;


template <typename T> using Func = function<T>;
// Expect
template <typename T> using Epct = Func<void (T &&)>;
// Standard Procedure, T -> U
template <typename T, typename U> using Proc = Func<void (T &&, Epct<U>)>;

template <typename... Ts> using PartGen = Func<void (Ts...)>;
// General Procedure, Us... -> T
template <typename T, typename... Us> using GenProc =
  Func<void (Epct<T>, Epct<PartGen<Us...>>)>;

template <typename... Ts> struct NestProc;
template <typename T, typename U> struct NestProc<T, U> {
  using Type = Proc<T, U>;
};
template <typename T, typename... Us> struct NestProc<T, Us...> {
  using Type = Proc<T, typename NestProc<Us...>::Type>;
};

template <typename T> struct RevGenProc : public RevGenProc<decltype(&T::operator())> {};
template <typename T, typename... Us, typename C>
struct RevGenProc<void (C::*)(Epct<T>, Epct<PartGen<Us...>>) const> {
  using RetType = T;
  template <template <typename...> class V> using ArgType = V<Us...>;
  using ProcType = typename NestProc<Us..., T>::Type;
};

template <typename T> struct RevProc;
template <typename T, typename U> struct RevProc<Proc<T, U>> {
  using ArgType = T;
  using RetType = U;
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


template <typename GP>
constexpr auto stand(GP &&gp) {
  using Ts = typename RevGenProc<GP>::template ArgType<Args>;
  using U = typename RevGenProc<GP>::RetType;

  if constexpr (Ts::atom) {
    // gp :: V -> U
    // gp :: void (Epct<U>, Epct<PartGen<V>>)
    // gp :: void (Epct<U>, Epct<Func<void (V &&)>>)
    using V = typename Ts::Head;
    return [&] (V &&v, Epct<U> pass) {
      gp(pass, [&] (PartGen<V> &&func) {
        func(move(v));
      });
    };
  }
  else {
    using V = typename Ts::Head;
    using Ws = typename Ts::template Tail<Args>;  // not used, but keep for `ws` below
    using X = typename Ts::template Tail<PartGen>;
    using Y = typename RevGenProc<GP>::ProcType;
    using Z = typename RevProc<Y>::RetType;
    // gp :: ~Ts... -> U
    // gp :: V -> ~Ws... -> U
    // Step 1, build a GenProc which is ~Ws... -> U
    // Step 2, use `stand` to turn it into standard shape
    // Step 3, prefix the passing of argument v and return it

    // step 3
    return [&] (V &&v, Epct<Z> pass) {
      // step 1
      // tail_gen_proc :: Ws... -> U
      // tail_gen_proc :: void (Epct<U>, Epct<PartGen<~Ws...>>)
      // tail_gen_proc :: void (Epct<U>, Epct<X>)
      auto tail_gen_proc = [&] (Epct<U> pass, Epct<X> intern_pass) {
        intern_pass([&] (auto &&...ws) {
          gp(pass, [&] (auto &&func) {
            func(move(v), move(ws)...);
          });
        });
      };
      // step 2
      pass(stand(move(tail_gen_proc)));
    };
  }
}

int main() {
  stand([] (Epct<int> pass, Epct<PartGen<int, int>> intern_pass) {
    intern_pass([&] (int &&x, int &&y) {
      pass(x + y);
    });
  })(3, [] (Proc<int, int> &&proc) {
    proc(5, [] (int &&eight) {
      cout << eight << endl;
    });
  });
}
