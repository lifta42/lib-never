#include <cstdlib>
#include "function.h"

int main(int argc, char *argv[]) {
never(
  start(argc, argv, [&] (int result) {
  never(
    std::exit(result)
  ))
)
