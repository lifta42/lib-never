#include <functional>
#include <iostream>
#include <utility>

using namespace std;

class Simple {
public:
  Simple() {
    cout << "cons" << endl;
  }
  Simple(const Simple &sp) {
    cout << "copy" << endl;
  }
};

int main() {
  function<void (int &&)> foo([] (int && _) {});
  foo(42);
  int x = 42;
  foo(move(x));
}
