#include "test.h"
#include <stdlib.h>

int main() {
  int result = exec();

  if (result != 0) {
    printf("\ntests failed.\n");
    return EXIT_FAILURE;
  }

  printf("\ntests were successful.\n");
  return EXIT_SUCCESS;
}