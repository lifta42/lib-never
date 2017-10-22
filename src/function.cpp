#include <iostream>
#include "function.h"

struct NeverExit {
  int code;
};

int main(int argc, char *argv[]) {
  try {
    start(argc, argv, [&] (int code) {
      throw NeverExit { code };
    });
  }
  catch (NeverExit &exiting) {
    return exiting.code;
  }
  catch (NeverReach &reaching) {
    std::cout << "libnever: executing never reached code at " << reaching.file
      << ":" << reaching.line << std::endl;
  }
}
