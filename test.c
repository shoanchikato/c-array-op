#include "test.h"
#include <stdlib.h>

int main() {
  int result = exec();

  if (result != 0) {
    printf("tests failed.\n");
    return EXIT_FAILURE;
  }

  printf("tests were successful.\n");
  return EXIT_SUCCESS;
}