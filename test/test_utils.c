#include "test_utils.h"
#include <stdio.h>

int unexpected_error(const char *test_name) {
  fprintf(stderr, "unexpected error in: %s\n", test_name);
  return EXIT_FAILURE;
}

int test_for_each(func tests[], size_t len) {
  int n = 0;
  for (int i = 0; i < len; i++) {
      n = tests[i]();
      if (n != 0) return EXIT_FAILURE;
  }

  return n;
}