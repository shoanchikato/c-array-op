#ifndef ARRAY_OP_H
#define ARRAY_OP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int array_op_insert(void **arr, size_t *len, void *element, size_t element_size);
int array_op_insert_at(void **arr, size_t *len, void *element, size_t element_size,
              size_t at_index);
int array_op_delete_at(void **arr, size_t *len, size_t element_size, size_t at_index);
void *array_op_get(void **arr, size_t len, size_t element_size, size_t at_index);

int array_op_push_front(void **arr, size_t *len, void *element, size_t element_size);
int array_op_push_back(void **arr, size_t *len, void *element, size_t element_size);
void *array_op_pop_front(void **arr, size_t *len, size_t element_size);
void *array_op_pop_back(void **arr, size_t *len, size_t element_size);

#endif // ARRAY_OP_H