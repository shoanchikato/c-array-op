#ifndef ARRAY_OP_H
#define ARRAY_OP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// INTERFACE
int insert(void **arr, size_t *len, void *element, size_t element_size);
int insert_at(void **arr, size_t *len, void *element, size_t element_size,
              size_t at_index);
int delete_at(void **arr, size_t *len, size_t element_size, size_t at_index);
void *get(void **arr, size_t len, size_t element_size, size_t at_index);

int push_front(void **arr, size_t *len, void *element, size_t element_size);
int push_back(void **arr, size_t *len, void *element, size_t element_size);
void *pop_front(void **arr, size_t *len, size_t element_size);
void *pop_back(void **arr, size_t *len, size_t element_size);

// IMPLEMENTATION
int insert(void **arr, size_t *len, void *element, size_t element_size) {
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

int insert_at(void **arr, size_t *len, void *element, size_t element_size,
              size_t at_index) {

  if (at_index >= *len + 1) {
    printf("error index is out of bounds.\n");
    return 1;
  }

  void *dst = malloc(element_size * (*len + 1));
  if (dst == NULL) {
    printf("error allocating memory for dst in insert_at\n");
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
    printf("error allocating memory for dst in insert_at\n");
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

  return (char *)*arr + (at_index * element_size);
}

int push_front(void **arr, size_t *len, void *element, size_t element_size) {
  size_t at_index = 0;

  return insert_at(arr, len, element, element_size, at_index);
}

int push_back(void **arr, size_t *len, void *element, size_t element_size) {
  return insert(arr, len, element, element_size);
}

void *_save_element_before_delete(void **arr, size_t *len, size_t element_size,
                                  size_t at_index) {
  void *result = get(arr, *len, element_size, at_index);
  if (result == NULL) {
    return result;
  }

  void *element = malloc(element_size);
  if (element == NULL) {
    printf("failed to allocate memory for element\n");
    return NULL;
  }

  if (result != NULL) {

    memcpy(element, result, element_size);
    delete_at(arr, len, element_size, at_index);

    return element;
  }

  return NULL;
}

void *pop_front(void **arr, size_t *len, size_t element_size) {
  size_t at_index = 0;

  return _save_element_before_delete(arr, len, element_size, at_index);
}

void *pop_back(void **arr, size_t *len, size_t element_size) {
  size_t at_index = *len - 1;

  return _save_element_before_delete(arr, len, element_size, at_index);
}

#endif // ARRAY_OP_H