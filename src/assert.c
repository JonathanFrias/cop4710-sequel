#include "common.h"

void assert(bool val, char msg[30]) {
  if(!val) {
    printf("Test fail!\n\tassertion failed with message: '%s'\n", msg);
    return;
  }
}
