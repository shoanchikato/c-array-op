#ifndef ARRAY_OP_H
#define ARRAY_OP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(void **arr, size_t *len, void *element, size_t element_size) {
  size_t arr_size = (*len) * element_size;

  *arr = realloc(*arr, arr_size + element_size);
  if (*arr == NULL) {
    printf("error allocating new arr memory\n");
    return;
  }

  memcpy((char *)(*arr) + arr_size, element, element_size);
  ++(*len);
}

int insert_at(void **arr, size_t *len, void *element, size_t element_size,
              size_t at_index) {

  if (at_index >= *len + 1) {
    printf("error index is out of bounds.\n");
    return 1;
  }

  void *dst = malloc(element_size * (*len + 1));
  if (dst == NULL) {
    printf("error allocating memory for dst in insert_at");
    return 1;
  }

  // copy to dst exclusive of index
  memcpy(dst, *arr, at_index * element_size);
  // copy new element
  memcpy((char *)dst + (at_index * element_size), element, element_size);
  // copy rest of the element inclusive of index
  memcpy((char *)dst + (at_index + 1) * element_size,
         (char *)(*arr) + at_index * element_size,
         (*len - at_index) * element_size);

  free(*arr);

  *arr = dst;
  (*len)++;

  return 0;
}

int delete_at(void **arr, size_t *len, size_t element_size, size_t at_index) {

  if (at_index >= *len) {
    printf("error index is out of bounds.\n");
    return 1;
  }

  void *dst = malloc(element_size * (*len - 1));
  if (dst == NULL) {
    printf("error allocating memory for dst in insert_at");
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

void *get(void **arr, size_t len, size_t element_size, size_t at_index) {
  if (at_index >= len) {
    printf("error index is out of bounds.\n");
    return NULL;
  }

  return (char *)arr + (at_index * element_size);
}

#endif // ARRAY_OP_H