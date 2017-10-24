#include <iostream>
#include <functional>
#include <utility>

using namespace std;


void modify(int &x, function<void ()> pass) {
  x++;
  pass();
}

int main() {
  int x = 42;
  modify(x, [&] () {
    cout << x << endl;
  });
  return 0;
}
