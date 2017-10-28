#include <iostream>
#include <functional>

using namespace std;

template <typename T> using Func = function<T>;
template <typename T> using Epct = Func<void (T)>;
template <typename... Ts> using PartGen = Func<void (Ts...)>;

template <typename T> struct RevEpct : public RevEpct<decltype(&T::operator())> {};
template <typename T, typename C> struct RevEpct<void (C::*)(T) const> {
  using Type = T;
};

template <typename F> auto foo(F func) {  // F: Epct<Epct<PartGen<int, double>>>
  using T = typename RevEpct<F>::Type;  // T: Epct<PartGen<int, double>>
  using U = typename RevEpct<T>::Type;  // U: PartGen<int, double>
  return [=] (auto ...vs) {
    func([=] (auto u) {
      u(vs...);
    });
  };
}

int main() {
  foo([] (auto k) {
    k([] (int x, double y) {
      // do something here
      cout << x << " " << y << endl;
    });
  })(42, 42.5);
}
