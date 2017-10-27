#include <iostream>
#include <utility>
#include <functional>

using namespace std;


template <typename T> using Func = std::function<T>;
template <typename T> using Cont = Func<void (T &&)>;
template <typename T, typename U> using Proc = Func<void (T &&, Cont<U>)>;

auto stand(Func<void (Cont<int>, Cont<Func<void (int &&, int &&)>>)> &&pc) {
  return [&] (int &&arg1, Cont<Proc<int, int>> pass1) {
    pass1([&] (int &&arg2, Cont<int> &&pass2) {
      pc(move(pass2), [&] (Func<void (int &&, int &&)> &&func) {
        func(move(arg1), move(arg2));
      });
    });
  };
}

int main() {
  stand([] (Cont<int> passing, Cont<Func<void (int &&, int &&)>> pass) {
    pass([&] (int &&x, int &&y) {
      passing(x + y);
    });
  })(3, [] (Proc<int, int> &&proc) {
    proc(5, [] (int &&eight) {
      cout << eight << endl;
    });
  });
}
