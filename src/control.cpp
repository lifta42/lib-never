#include "control.h"

Never when(FuncR<bool> cond, ContV tc, ContV fc) {
never(
  if (cond()) {
  never(
    tc();
  )
  else {
  never(
    fc();
  )
)
