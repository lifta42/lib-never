#include <iostream>
#include <functional>

using namespace std;

class Simple {
public:
  int id;
  static int count;
  Simple() {
    id = count++;
    cout << "constructing " << id << endl;
  }
  Simple(function<void ()> func) {
    id = count++;
    cout << "constructing " << id << " with a function" << endl;
  }
  Simple(const Simple &sp) {
    id = count++;
    cout << "copying " << sp.id << " to " << id << endl;
  }
  ~Simple() {
    cout << "deconstructing " << id << endl;
  }
};
int Simple::count = 0;

void foo(Simple simple) {}

void bar() {}

int main() {
  {
    Simple simple;
    foo(simple);
  }
  {
    foo(Simple());
  }
  {
    foo(Simple(bar));
  }
  return 0;
}
