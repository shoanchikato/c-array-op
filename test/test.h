#ifndef TEST_H
#define TEST_H

#include "../include/array_op.h"
#include "errno.h"
#include "stdio.h"
#include <stdlib.h>

int unexpected_error(const char *test_name) {
  printf("unexpected error in: %s\n", test_name);
  return EXIT_FAILURE;
}

int test_insert_len();
int test_insert_element();
int test_insert_at_len();
int test_insert_at_element();
int test_delete_at_len();
int test_delete_at_element();
int test_get_element();

int test_push_front();
int test_push_back();
int test_pop_front();
int test_pop_back();

int test_insert_len() {
  // arrange
  const char *test_name = "test_insert_len";
  int *nums = NULL;
  int n1 = 100;

  size_t got = 0;
  size_t expect = 1;

  // act
  int n = insert((void **)&nums, &got, &n1, sizeof(int));
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  if (expect != got) {
    printf("%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_element() {
  // arrange
  const char *test_name = "test_insert_element";
  int *nums = NULL;
  int expect = 100;

  size_t len = 0;

  // act
  int n = insert((void **)&nums, &len, &expect, sizeof(int));
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  int got = nums[0];
  if (expect != got) {
    printf("%s: expect %d, got %d\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_len() {
  // arrange
  const char *test_name = "test_insert_at_len";
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
  int n = insert_at((void **)&nums, &got, &n1, sizeof(int), at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  if (expect != got) {
    printf("%s: expect %lu, got %lu\n", test_name, expect, got);
    return EXIT_FAILURE;
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_insert_at_element() {
  // arrange
  const char *test_name = "test_insert_at_element";
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
  int n = insert_at((void **)&nums, &len, &n1, sizeof(int), at_index);
  if (n != 0) {
    return unexpected_error(test_name);
  }
  int got = 0;

  // assert
  for (int i = 0; i < 5; i++) {
    got = nums[i];

    if (expect[i] != got) {
      printf("%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_len() {
  // arrange
  const char *test_name = "test_delete_at_len";
  size_t got = 4;
  int *nums = (int *)calloc(got, got * sizeof(int));
  nums[0] = 1;
  nums[1] = 2;
  nums[2] = 3;
  nums[3] = 4;

  size_t expect[4] = {3, 2, 1, 0};

  // act
  for (int i = 0; i < 4; i++) {
    int n = delete_at((void **)&nums, &got, sizeof(int), 0);
    if (n != 0) {
      return unexpected_error(test_name);
    }
    // assert
    if (expect[i] != got) {
      printf("%s: expect %lu, got %lu\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_delete_at_element() {
  // arrange
  const char *test_name = "test_delete_at_element";
  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[3] = {24, 35, 46};
  int got = 0;

  // act
  int n = delete_at((void **)&nums, &len, sizeof(int), 0);
  if (n != 0) {
    return unexpected_error(test_name);
  }

  // assert
  for (int i = 0; i < 3; i++) {
    got = nums[i];

    if (expect[i] != got) {
      printf("%s: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_get_element() {
  // arrange
  const char *test_name = "test_get_element";
  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[4] = {13, 24, 35, 46};
  int *got = 0;

  for (int i = 0; i < 4; i++) {
    // act
    got = (int *)get((void **)&nums, len, sizeof(int), i);
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect[i] != *got) {
      printf("%s: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_push_front() {
  // arrange
  const char *test_name = "test_push_front";
  int *nums = NULL;
  size_t len = 0;
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = push_front((void **)&nums, &len, &value[i], sizeof(int));
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = nums[0];

    // assert
    if (expect_len[i] != len) {
      printf("%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      printf("%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_push_back() {
  // arrange
  const char *test_name = "test_push_back";
  int *nums = NULL;
  size_t len = 0;
  int value[] = {13, 24, 35, 46};

  int expect[] = {13, 24, 35, 46};
  size_t expect_len[] = {1, 2, 3, 4}; 

  // act
  for (int i = 0; i < 4; i++) {
    int n = push_back((void **)&nums, &len, &value[i], sizeof(int));
    if (n != 0) {
      return unexpected_error(test_name);
    }
    int got = nums[len-1];

    // assert
    if (expect_len[i] != len) {
      printf("%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != got) {
      printf("%s: element test: expect %d, got %d\n", test_name, expect[i], got);
      return EXIT_FAILURE;
    }
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_pop_front() {
  // arrange
  const char *test_name = "test_pop_front";
  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect[4] = {13, 24, 35, 46};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = 0;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) pop_front((void **)&nums, &len, sizeof(int));
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != len) {
      printf("%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      printf("%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  free(nums);
  return EXIT_SUCCESS;
}

int test_pop_back() {
  // arrange
  const char *test_name = "test_pop_back";
  size_t len = 4;
  int *nums = (int *)calloc(len, len * sizeof(int));
  nums[0] = 13;
  nums[1] = 24;
  nums[2] = 35;
  nums[3] = 46;

  int expect [] = {46, 35, 24, 13};
  size_t expect_len[] = {3, 2, 1, 0}; 

  int *got = 0;

  // act
  for (int i = 0; i < 4; i++) {
    got = (int*) pop_back((void **)&nums, &len, sizeof(int));
    if (got == NULL) {
      return unexpected_error(test_name);
    }

    // assert
    if (expect_len[i] != len) {
      printf("%s: len test: expect %zu, got %zu\n", test_name, expect_len[i], len);
      return EXIT_FAILURE;
    }

    if (expect[i] != *got) {
      printf("%s: element test: expect %d, got %d\n", test_name, expect[i], *got);
      return EXIT_FAILURE;
    }

    free(got);
  }

  free(nums);
  return EXIT_SUCCESS;
}

int exec() {
  int n = 0;

  n = test_insert_element();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_insert_len();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_insert_at_element();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_insert_at_len();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_delete_at_len();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_delete_at_element();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_get_element();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_push_front();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_push_back();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_pop_front();
  if (n != 0)
    return EXIT_FAILURE;

  n = test_pop_back();
  if (n != 0)
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

#endif // TEST_H