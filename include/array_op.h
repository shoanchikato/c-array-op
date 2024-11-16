#ifndef ARRAY_OP_H
#define ARRAY_OP_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOW LEVEL API

int array_op_insert(void **arr, size_t *len, void *element, size_t element_size);
int array_op_insert_at(void **arr, size_t *len, void *element, size_t element_size,
              size_t at_index);
int array_op_delete_at(void **arr, size_t *len, size_t element_size, size_t at_index);
void *array_op_get(void **arr, size_t len, size_t element_size, size_t at_index);

int array_op_push_front(void **arr, size_t *len, void *element, size_t element_size);
int array_op_push_back(void **arr, size_t *len, void *element, size_t element_size);
void *array_op_pop_front(void **arr, size_t *len, size_t element_size);
void *array_op_pop_back(void **arr, size_t *len, size_t element_size);

// HIGH LEVEL API

typedef struct {
  size_t capacity;
  size_t len;
  size_t element_size;
  void **arr;
} Arr;

Arr *array_op_init_s(size_t element_size);

int array_op_insert_s(Arr *arr, void *element);
int array_op_insert_at_s(Arr *arr, void *element, size_t at_index);
int array_op_delete_at_s(Arr *arr, size_t at_index);
void *array_op_get_s(Arr *arr, size_t at_index);

int array_op_push_front_s(Arr *arr, void *element);
int array_op_push_back_s(Arr *arr, void *element);
void *array_op_pop_front_s(Arr *arr);
void *array_op_pop_back_s(Arr *arr);

void array_op_free_s(Arr *arr);

#endif // ARRAY_OP_H