#include "../include/array_op.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOW LEVEL API

int array_op_insert(void **arr, size_t *len, void *element, size_t element_size) {
  size_t arr_size = (*len) * element_size;

  *arr = realloc(*arr, arr_size + element_size);
  if (*arr == NULL) {
    printf("error allocating new arr memory\n");
    return 1;
  }

  memcpy((char *)(*arr) + arr_size, element, element_size);
  ++(*len);

  return 0;
}

int array_op_insert_at(void **arr, size_t *len, void *element, size_t element_size, size_t at_index) {

  if (at_index >= *len + 1) {
    printf("error index is out of bounds.\n");
    return 1;
  }

  void *dst = calloc((*len + 1), element_size);
  if (dst == NULL) {
    printf("error allocating memory for dst in array_op_insert_at\n");
    return 1;
  }

  if (*arr == NULL) {
    memcpy((char *)dst + (at_index * element_size), element, element_size);
  } else {
    // copy to dst exclusive of index
    memcpy(dst, *arr, at_index * element_size);
    // copy new element
    memcpy((char *)dst + (at_index * element_size), element, element_size);
    // copy rest of the element inclusive of index
    memcpy((char *)dst + (at_index + 1) * element_size,
           (char *)(*arr) + at_index * element_size,
           (*len - at_index) * element_size);
  }

  free(*arr);

  *arr = dst;
  (*len)++;

  return 0;
}

int array_op_delete_at(void **arr, size_t *len, size_t element_size, size_t at_index) {

  if (at_index >= *len) {
    printf("error index is out of bounds.\n");
    return 1;
  }

  void *dst = calloc((*len - 1), element_size);
  if (dst == NULL) {
    printf("error allocating memory for dst in array_op_insert_at\n");
    return 1;
  }

  // copy to dst exclusive of index
  memcpy(dst, *arr, at_index * element_size);
  // copy rest of the element exclusive of index
  memcpy((char *)dst + at_index * element_size,
         (char *)(*arr) + (at_index + 1) * element_size,
         (*len - at_index - 1) * element_size);

  free(*arr);

  *arr = dst;
  (*len)--;

  return 0;
}

void *array_op_get(void **arr, size_t len, size_t element_size, size_t at_index) {
  if (at_index >= len) {
    printf("error index is out of bounds.\n");
    return NULL;
  }

  return (char *)*arr + (at_index * element_size);
}

int array_op_push_front(void **arr, size_t *len, void *element,
                        size_t element_size) {
  size_t at_index = 0;

  return array_op_insert_at(arr, len, element, element_size, at_index);
}

int array_op_push_back(void **arr, size_t *len, void *element, size_t element_size) {
  return array_op_insert(arr, len, element, element_size);
}

void *_save_element_before_delete(void **arr, size_t *len, size_t element_size, size_t at_index) {
  void *result = array_op_get(arr, *len, element_size, at_index);
  if (result == NULL) {
    return result;
  }

  void *element = calloc(1, element_size);
  if (element == NULL) {
    printf("failed to allocate memory for element\n");
    return NULL;
  }

  if (result != NULL) {

    memcpy(element, result, element_size);
    array_op_delete_at(arr, len, element_size, at_index);

    return element;
  }

  return NULL;
}

void *array_op_pop_front(void **arr, size_t *len, size_t element_size) {
  size_t at_index = 0;

  return _save_element_before_delete(arr, len, element_size, at_index);
}

void *array_op_pop_back(void **arr, size_t *len, size_t element_size) {
  size_t at_index = *len - 1;

  return _save_element_before_delete(arr, len, element_size, at_index);
}

// 

Arr *array_op_init_s(size_t element_size) {
  Arr *arr = (Arr *)malloc(sizeof(Arr));
  if (arr == NULL) {
    perror("failed to allocated memory for arr\n");
    exit(1);
  }

  arr->arr = NULL;
  arr->element_size = element_size;
  arr->len = 0;

  return arr;
}

int array_op_insert_s(Arr *arr, void *element) {
  return array_op_insert((void **)&arr->arr, &arr->len, element, arr->element_size);
}

int array_op_insert_at_s(Arr *arr, void *element, size_t at_index) {
  return array_op_insert_at((void **)&arr->arr, &arr->len, element,arr->element_size, at_index);
}

int array_op_delete_at_s(Arr *arr, size_t at_index) {
  return array_op_delete_at((void **)&arr->arr, &arr->len, arr->element_size, at_index);
}

void *array_op_get_s(Arr *arr, size_t at_index) {
  return array_op_get((void **)&arr->arr, arr->len, arr->element_size, at_index);
}

int array_op_push_front_s(Arr *arr, void *element) {
  return array_op_push_front((void **)&arr->arr, &arr->len, element,arr->element_size);
}

int array_op_push_back_s(Arr *arr, void *element) {
  return array_op_push_back((void **)&arr->arr, &arr->len, element,arr->element_size);
}

void *array_op_pop_front_s(Arr *arr) {
  return array_op_pop_front((void **)&arr->arr, &arr->len, arr->element_size);
}

void *array_op_pop_back_s(Arr *arr) {
  return array_op_pop_back((void **)&arr->arr, &arr->len, arr->element_size);
}

void array_op_free_s(Arr *arr) {
  if (arr == NULL)
    return;

  free(arr);
}