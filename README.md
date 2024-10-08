# Array Op

This project offers basic functions for manipulating dynamically allocated arrays in C. It includes functions to insert and delete elements at specific indexes, and to retrieve elements from the array.

## Features

- **Insert an element into a dynamically allocated array**.
- **Insert an element at a specific index in a dynamically allocated array**.
- **Delete an element from a dynamically allocated array**.
- **Retrieve an element from a dynamically allocated array by index**.
- **Insert an element at the front of a dynamically allocated array**.
- **Insert an element at the back of a dynamically allocated array**.
- **Remove and return the first element from a dynamically allocated array**.
- **Remove and return the last element from a dynamically allocated array**.

## Usage

1. **Add the header file**:  
   Place the header file (`array_op.h`) in the `./include` folder or any other directory where your project stores header files.

2. **Add source file**:  
   Place the source files (`array_op.c`) in the `./src` folder or any other directory where your project stores source files.

3. **Compile your program**:  
   When compiling, use the `-I` flag to include the directory where the header file is located.  
   Example:
   ```bash
   gcc -Wall -I./include -o my_program array_op.c my_program.c
   ```

## Functions

### Insert

```c
int array_op_insert(void **arr, size_t *len, void *element, size_t element_size);
```

This function inserts a new element at the end of a dynamically allocated array.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `void *element`: A pointer to the element to be inserted.
- `size_t element_size`: The size of each element in the array (in bytes).

#### Return Value

- Returns `0` on success.
- Returns `1` if an error occurs (e.g., memory allocation failure).

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    int *nums = NULL;
    size_t len = 0;

    int n = 100;

    array_op_insert((void **) &nums, &len, &n, sizeof(int));

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### Insert At

```c
int array_op_insert_at(void **arr, size_t *len, void *element, size_t element_size, size_t at_index);
```

This function inserts a new element at a specified index in a dynamically allocated array.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `void *element`: A pointer to the element to be inserted.
- `size_t element_size`: The size of each element in the array (in bytes).
- `size_t at_index`: The index at which the element should be inserted.

#### Return Value

- Returns `0` on success.
- Returns `1` if an error occurs (e.g., memory allocation failure).

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 4;
    int *nums = (int *)calloc(len, len * sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;
    nums[3] = 46;

    int n = 100;

    array_op_insert_at((void **) &nums, &len, &n, sizeof(int), 2);

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### Delete At

```c
int array_op_delete_at(void **arr, size_t *len, size_t element_size, size_t at_index);
```

This function deletes an element from a dynamically allocated array at the specified index.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `size_t element_size`: The size of each element in the array (in bytes).
- `size_t at_index`: The index of the element to be deleted.

#### Return Value

- Returns `0` on success.
- Returns `1` if an error occurs (e.g., memory allocation failure).

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 4;
    int *nums = (int *)calloc(len, len * sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;
    nums[3] = 46;

    array_op_delete_at((void **) &nums, &len, sizeof(int), 1);

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### Get

```c
void *array_op_get(void **arr, size_t len, size_t element_size, size_t at_index);
```

This function retrieves an element from a dynamically allocated array by index.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t len`: The length of the array.
- `size_t element_size`: The size of each element in the array (in bytes).
- `size_t at_index`: The index of the element to retrieve.

#### Return Value

- Returns a pointer to the element at the specified index.
- Returns `NULL` if the index is out of bounds.

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 4;
    int *nums = (int *)calloc(len, len * sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;
    nums[3] = 46;

    int index = 2;

    int *result = (int *)array_op_get((void **) &nums, len, sizeof(int), index);
    if (result) {
        printf("Value at index %d: %d\n", index, *result);
    }

    free(nums);
    return 0;
}
```

### Push Front

```c
int array_op_push_front(void **arr, size_t *len, void *element, size_t element_size);
```

This function inserts an element at the front of a dynamically allocated array.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `void *element`: A pointer to the element to be inserted.
- `size_t element_size`: The size of each element in the array (in bytes).

#### Return Value

- Returns `0` on success.
- Returns `1` if an error occurs (e.g., memory allocation failure).

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 3;
    int *nums = (int *)calloc(len, sizeof(int));
    nums[0] = 24;
    nums[1] = 35;
    nums[2] = 46;

    int new_num = 13;
    array_op_push_front((void **)&nums, &len, &new_num, sizeof(int));

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### Push Back

```c
int array_op_push_back(void **arr, size_t *len, void *element, size_t element_size);
```

This function appends an element to the end of a dynamically allocated array, identical to [insert](#insert).

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `void *element`: A pointer to the element to be inserted.
- `size_t element_size`: The size of each element in the array (in bytes).

#### Return Value

- Returns `0` on success.
- Returns `1` if an error occurs (e.g., memory allocation failure).

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 3;
    int *nums = (int *)calloc(len, sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;

    int new_num = 46;
    array_op_push_back((void **)&nums, &len, &new_num, sizeof(int));

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### Pop Front

```c
void *array_op_pop_front(void **arr, size_t *len, size_t element_size);
```

Removes and returns the first element from a dynamic array, whose memory needs to be freed.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `size_t element_size`: The size of each element in the array (in bytes).

#### Return Value

- A pointer to the first element that was removed from the array. The caller is responsible for managing the memory of the returned element.
- Returns `NULL` if the index is out of bounds, or if there is an error.

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 3;
    int *nums = (int *)calloc(len, sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;

    int *first_element = array_op_pop_front((void **)&nums, &len, sizeof(int));
    printf("Popped first element: %d\n", *first_element);
    
    free(first_element);
    free(nums);

    return 0;
}
```

### Pop Back

```c
void *array_op_pop_back(void **arr, size_t *len, size_t element_size);
```

Removes and returns the last element from a dynamic array, whose memory needs to be freed.

#### Parameters

- `void **arr`: A pointer to the dynamically allocated array.
- `size_t *len`: A pointer to the length of the array.
- `size_t element_size`: The size of each element in the array (in bytes).

#### Return Value

- A pointer to the last element that was removed from the array. The caller is responsible for managing the memory of the returned element.
- Returns `NULL` if the index is out of bounds, or if there is an error.

#### Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "include/array_op.h"

int main() {
    size_t len = 3;
    int *nums = (int *)calloc(len, sizeof(int));
    nums[0] = 13;
    nums[1] = 24;
    nums[2] = 35;

    int *last_element = array_op_pop_back((void **)&nums, &len, sizeof(int));
    printf("Popped last element: %d\n", *last_element);
    
    free(last_element);
    free(nums);

    return 0;
}
```

#### Licence

This project is licensed under the MIT License - see the [LICENSE](/LICENSE) file for details.
