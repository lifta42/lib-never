#include "control.h"

Never when(FuncR<bool> cond, ContV tc, ContV fc) {
  if (cond()) {
  never(
    tc();
  )
  else {
  never(
    fc();
  )
}
