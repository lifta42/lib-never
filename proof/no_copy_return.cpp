#include <iostream>

using namespace std;


class Simple {
public:
  int value;
  Simple() {
    cout << "cons" << endl;
    value = 42;
  }
  Simple(const Simple &sp) {
    cout << "copy" << endl;
  }
  Simple(Simple &&sp) {
    cout << "move" << endl;
  }
};

Simple foo() {
  return Simple();
}

int main() {
  Simple simple = foo();
  int x = foo().value;
  return 0;
}
