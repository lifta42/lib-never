#include <iostream>
#include <string>

using namespace std;


template <typename... Ts> struct Bar;
template <typename T> struct Bar<int, T> {
  static string desc;
};
template <typename T> string Bar<int, T>::desc = "int";

template <typename T> struct Bar<string, T> {
  static string desc;
};
template <typename T> string Bar<string, T>::desc = "string";

template <typename... Ts> auto bar(Ts ...ts) {
  return Bar<Ts...>::desc;
}

auto foo() {
  return [] (auto ...xs) {
    return bar(xs...);
  };
}


int main() {
  cout << foo()(42, 84) << endl;
  cout << foo()(string("some"), 84) << endl;
}
