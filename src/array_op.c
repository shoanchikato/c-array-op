#include "../include/array_op.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// LOW LEVEL API

int array_op_insert(void **arr, size_t *len, void *element, size_t element_size) {
  if(!element) {
    printf("error null element provided\n");
    return 1;
  }

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
  if(!arr || !element) {
    printf("error null arr or element, index: %zu, len: %zu\n", at_index, *len);
    return 1;
  }

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

// HIGH LEVEL API

Arr *array_op_init_s(size_t element_size) {
  Arr *arr = (Arr *)malloc(sizeof(Arr));
  if (arr == NULL) {
    perror("error failed to allocated memory for arr\n");
    exit(1);
  }

  void *content = calloc(element_size, 4);

  arr->arr = content;
  arr->element_size = element_size;
  arr->len = 0;
  arr->capacity = 4;

  return arr;
}

int reallocate(Arr *arr) {
  void *content = realloc(arr->arr, (arr->element_size * arr->capacity * 2));
  if (content == NULL) {
    printf("error allocating more arrary memory\n");
    return 1;
  }

  arr->arr = content;
  arr->capacity = arr->capacity * 2;

  return 0;
}

int shrink_reallocate(Arr *arr) {
    // Only shrink if capacity is more than 2 and usage is less than or equal to half
    if (arr->capacity > 2 && arr->len <= arr->capacity / 2) {
        size_t new_capacity = arr->capacity / 2;
        void *new_arr = realloc(arr->arr, new_capacity * arr->element_size);

        if (new_arr == NULL) {
            printf("error reallocating to less array memory\n");
            return 1;
        }

        arr->arr = new_arr;
        arr->capacity = new_capacity;
    }

    return 0;
}

int array_op_insert_s(Arr *arr, void *element) {
  if(!arr || !element) {
    printf("error null arr or element\n");
    return 1;
  }

  if(arr->len >= arr->capacity) {
    if(reallocate(arr) != 0) {
      return 1;
    }
  }

  memcpy((char *)arr->arr + (arr->len * arr->element_size), element, arr->element_size);
  arr->len++;

  return 0;
}

int array_op_insert_at_s(Arr *arr, void *element, size_t at_index) {
  if(!arr || !element) {
    printf("error null arr or element, index: %zu, len: %zu\n", at_index, arr->len);
    return 1;
  }

  if (at_index > arr->len) {
    printf("error index is out of bounds, index: %zu, len: %zu\n", at_index, arr->len);
    return 1;
  }

  if(arr->len >= arr->capacity) {
    if(reallocate(arr) != 0) {
      return 1;
    }
  }

  if (at_index < arr->len) {
    memmove((char *)arr->arr + (at_index + 1) * arr->element_size, 
            (char *)arr->arr + at_index * arr->element_size, 
            (arr->len - at_index) * arr->element_size);
  }

  memcpy((char *)arr->arr + at_index * arr->element_size, element, arr->element_size);
  arr->len++;

  return 0;
}

int array_op_delete_at_s(Arr *arr, size_t at_index) {
  if (at_index >= arr->len) {
    printf("error index is out of bounds, index: %zu, len: %zu\n", at_index, arr->len);
    return 1;
  }

  if(shrink_reallocate(arr) != 0) {
    return 1;
  }

  memmove((char *)arr->arr + (at_index * arr->element_size), 
          (char *)arr->arr + (at_index + 1) * arr->element_size, 
          (arr->len - 1 - at_index) * arr->element_size);
  arr->len--;

  return 0;
}

void *array_op_get_s(Arr *arr, size_t at_index) {
  return array_op_get((void **)&arr->arr, arr->len, arr->element_size, at_index);
}

int array_op_push_front_s(Arr *arr, void *element) {
  return array_op_insert_at_s(arr, element, 0);
}

int array_op_push_back_s(Arr *arr, void *element) {
  return array_op_insert_s(arr, element);
}

void *_save_element_before_delete_s(Arr *arr, size_t at_index) {
  void *result = array_op_get_s(arr, at_index);
  if (result == NULL) {
    return result;
  }

  void *element = calloc(1, arr->element_size);
  if (element == NULL) {
    printf("failed to allocate memory for element\n");
    return NULL;
  }

  if (result != NULL) {

    memcpy(element, result, arr->element_size);
    array_op_delete_at_s(arr, at_index);

    return element;
  }

  return NULL;
}

void *array_op_pop_front_s(Arr *arr) {
  size_t at_index = 0;
  
  return _save_element_before_delete_s(arr, at_index);
}

void *array_op_pop_back_s(Arr *arr) {
  size_t at_index = arr->len - 1;
  
  return _save_element_before_delete_s(arr, at_index);
}

void array_op_free_s(Arr *arr) {
  if (arr == NULL)
    return;

  free(arr->arr);
  free(arr);
}