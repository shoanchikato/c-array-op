#include "../include/array_op.h"
#include "test_utils.h"
#include "test.h"
#include "test_s.h"
#include "errno.h"
#include "stdio.h"
#include <stdlib.h>

int test_insert_len_s() {
  // arrange
  const char *test_name = "test_insert_len_s";
  fprintf(stderr, "running %s\n", test_name);

  Arr *nums = array_op_init_s(sizeof(int));
  int n1 = 100;

  size_t expect = 1;

  // act
  int n = array_op_insert_s(nums, &n1);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  size_t got = nums->len;
  if (expect != got) {
    fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_insert_element_s() {
  // arrange
  const char *test_name = "test_insert_element_s";
  fprintf(stderr, "running %s\n", test_name);

  Arr *nums = array_op_init_s(sizeof(int));
  int n1 = 100;
  int expect = 100;

  // act
  int n = array_op_insert_s(nums, &n1);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  int got = *((int *)array_op_get_s(nums, 0));
  if (expect != got) {
    fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_len_s() {
  // arrange
  const char *test_name = "test_insert_at_len_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int n1 = 100;
  size_t at_index = 2;

  size_t expect = 5;

  // act
  int n = array_op_insert_at_s(nums, &n1, at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  size_t got = nums->len;
  if (expect != got) {
    fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_element_s() {
  // arrange
  const char *test_name = "test_insert_at_element_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int n1 = 100;

  int expect[5] = {13, 24, 35, 100, 46};
  size_t at_index = 3;

  // act
  int n = array_op_insert_at_s(nums, &n1, at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }
  int got = 0;

  // assert
  for (int i = 0; i < 5; i++) {
    got = *((int *)array_op_get_s(nums, i));

    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_len_s() {
  // arrange
  const char *test_name = "test_delete_at_len_s";
  fprintf(stderr, "running %s\n", test_name);
  
  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 4;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  size_t expect[4] = {3, 2, 1, 0};
  size_t at_index = 0;

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_delete_at_s(nums, at_index);
    if (n != 0) {
      return unexpected_error(test_name);
    }
    // assert
    size_t got = nums->len;
    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %lu, got %lu\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_element_s() {
  // arrange
  const char *test_name = "test_delete_at_element_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int expect[3] = {24, 35, 46};
  int got = 0;

  size_t at_index = 0;

  // act
  int n = array_op_delete_at_s(nums, at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  for (int i = 0; i < 3; i++) {
    got = *((int *)array_op_get_s(nums, i));

    if (expect[i] != got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_get_element_s() {
  // arrange
  const char *test_name = "test_get_element_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int expect[4] = {13, 24, 35, 46};
  int *got = NULL;

  for (int i = 0; i < 4; i++) {
    // act
    got = (int *)array_op_get_s(nums, i);
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect[i] != *got) {
      fprintf(stderr, "%s: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_array_op_push_front_s() {
  // arrange
  const char *test_name = "test_push_front_s";
  fprintf(stderr, "running %s\n", test_name);

  Arr *nums = array_op_init_s(sizeof(int));
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_push_front_s(nums,&value[i]);
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = *((int *) array_op_get_s(nums, 0));

    // assert
    if (expect_len[i] != nums->len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], nums->len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_array_op_push_back_s() {
  // arrange
  const char *test_name = "test_push_back_s";
  fprintf(stderr, "running %s\n", test_name);

  Arr *nums = array_op_init_s(sizeof(int));
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = array_op_push_back_s(nums, &value[i]);
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = *((int*) array_op_get_s(nums, nums->len-1));

    // assert
    if (expect_len[i] != nums->len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], nums->len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_array_op_pop_front_s() {
  // arrange
  const char *test_name = "test_pop_front_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = NULL;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) array_op_pop_front_s(nums);
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != nums->len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], nums->len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int test_array_op_pop_back_s() {
  // arrange
  const char *test_name = "test_pop_back_s";
  fprintf(stderr, "running %s\n", test_name);

  size_t len = 4;
  int *arr = (int *)calloc(len, len * sizeof(int));
  arr[0] = 13;
  arr[1] = 24;
  arr[2] = 35;
  arr[3] = 46;

  Arr *nums = array_op_init_s(sizeof(int));
  free(nums->arr); // when mutually assigning
  nums->arr = (void **)arr;
  nums->len = len;
  nums->capacity = len;

  int expect [] = {46, 35, 24, 13};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = NULL;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) array_op_pop_back_s(nums);
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != nums->len) {
      fprintf(stderr, "%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], nums->len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      fprintf(stderr, "%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  array_op_free_s(nums);
  return EXIT_SUCCESS;
}

int exec_test_s() {

  func tests[] = {
    test_insert_len_s,
    test_insert_element_s,
    test_insert_at_len_s,
    test_insert_at_element_s,
    test_delete_at_len_s,
    test_delete_at_element_s,
    test_get_element_s,
    
    test_array_op_push_front_s,
    test_array_op_push_back_s,
    test_array_op_pop_front_s,
    test_array_op_pop_back_s,
  };

  size_t len = sizeof(tests) / sizeof(tests[0]);

  int n = test_for_each(tests, len);

  return n;
}