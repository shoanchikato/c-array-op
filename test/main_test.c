#include "test.h"
#include "test_s.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int result = 0;

  result = exec_test();
  if (result != 0) {
    printf("\ntests failed.\n");
    return EXIT_FAILURE;
  }

  result = exec_test_s();
  if (result != 0) {
    printf("\ntests failed.\n");
    return EXIT_FAILURE;
  }

  printf("\ntests were successful.\n");
  return EXIT_SUCCESS;
}