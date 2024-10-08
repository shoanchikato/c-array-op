#include "../include/array_op.h"
#include "test_utils.h"
#include "test.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int test_insert_len() {
  // arrange
  const char *test_name = "test_insert_len";
  fprintf(stderr, "running %s\n", test_name);

  int *nums = NULL;
  int n1 = 100;

  size_t got = 0;
  size_t expect = 1;

  // act
  int n = array_op_insert((void **)&nums, &got, &n1, sizeof(int));
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  if (expect != got) {
    fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_element() {
  // arrange
  const char *test_name = "test_insert_element";
  fprintf(stderr, "running %s\n", test_name);

  int *nums = NULL;
  size_t len = 0;
  int n1 = 100;

  int expect = 100;

  // act
  int n = array_op_insert((void **)&nums, &len, &n1, sizeof(int));
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  int got = nums[0];
  if (expect != got) {
    fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_len() {
  // arrange
  const char *test_name = "test_insert_at_len";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int n1 = 100;
  size_t at_index = 2;

  size_t expect = 5;
  size_t got = len;

  // act
  int n = array_op_insert_at((void **)&nums, &got, &n1, sizeof(int), at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  if (expect != got) {
    fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_element() {
  // arrange
  const char *test_name = "test_insert_at_element";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int n1 = 100;

  int expect[5] = {13, 24, 35, 100, 46};
  size_t at_index = 3;

  // act
  int n = array_op_insert_at((void **)&nums, &len, &n1, sizeof(int), at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }
  int got = 0;

  // assert
  for (int i = 0; i < 5; i++) {
    got = nums[i];

    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_len() {
  // arrange
  const char *test_name = "test_delete_at_len";
  fprintf(stderr, "running %s\n", test_name);
  
  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 1;
  nums[1] = 2;
  nums[2] = 3;
  nums[3] = 4;

  size_t got = len;
  size_t expect[4] = {3, 2, 1, 0};

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_delete_at((void **)&nums, &got, sizeof(int), 0);
    if (n != 0) {
      return unexpected_error(test_name);
    }
    // assert
    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_element() {
  // arrange
  const char *test_name = "test_delete_at_element";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[3] = {24, 35, 46};
  int got = 0;

  // act
  int n = array_op_delete_at((void **)&nums, &len, sizeof(int), 0);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  for (int i = 0; i < 3; i++) {
    got = nums[i];

    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_get_element() {
  // arrange
  const char *test_name = "test_get_element";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[4] = {13, 24, 35, 46};
  int *got = NULL;

  for (int i = 0; i < 4; i++) {
    // act
    got = (int *)array_op_get((void **)&nums, len, sizeof(int), i);
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect[i] != *got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_array_op_push_front() {
  // arrange
  const char *test_name = "test_push_front";
  fprintf(stderr, "running %s\n", test_name);

  int *nums = NULL;
  size_t len = 0;
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_push_front((void **)&nums, &len, &value[i], sizeof(int));
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = nums[0];

    // assert
    if (expect_len[i] != len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_array_op_push_back() {
  // arrange
  const char *test_name = "test_push_back";
  fprintf(stderr, "running %s\n", test_name);

  int *nums = NULL;
  size_t len = 0;
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_push_back((void **)&nums, &len, &value[i], sizeof(int));
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = nums[len-1];

    // assert
    if (expect_len[i] != len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_array_op_pop_front() {
  // arrange
  const char *test_name = "test_pop_front";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = NULL;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) array_op_pop_front((void **)&nums, &len, sizeof(int));
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_array_op_pop_back() {
  // arrange
  const char *test_name = "test_pop_back";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect [] = {46, 35, 24, 13};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = NULL;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) array_op_pop_back((void **)&nums, &len, sizeof(int));
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  free(nums);
  return EXIT_SUCCESS;
}

int exec_test() {

  func tests[] = {
    test_insert_len,
    test_insert_element,
    test_insert_at_len,
    test_insert_at_element,
    test_delete_at_len,
    test_delete_at_element,
    test_get_element,
    
    test_array_op_push_front,
    test_array_op_push_back,
    test_array_op_pop_front,
    test_array_op_pop_back,
  };

  size_t len = sizeof(tests) / sizeof(tests[0]);

  int n = test_for_each(tests, len);

  return n;
}