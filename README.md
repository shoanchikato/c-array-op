# Array Op

This project provides basic functions for manipulating dynamically allocated arrays in C. It includes functions to insert and delete elements at specific indexes, and to retrieve elements from the array.

## Features

- **Insert an element into a dynamically allocated array**.
- **Insert an element at a specific index in a dynamically allocated array**.
- **Delete an element from a dynamically allocated array**.
- **Retrieve an element from a dynamically allocated array by index**.

## Functions

### 1. Insert

```c
int insert(void **arr, size_t *len, void *element, size_t element_size);
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

    insert((void **) &nums, &len, &new_num, sizeof(int));

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    free(nums);
    return 0;
}
```

### 2. Insert At

```c
int insert_at(void **arr, size_t *len, void *element, size_t element_size, size_t at_index);
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
    size_t len = 3;
    int nums[] = {1, 2, 4};
    int new_num = 3;

    insert_at((void **) &nums, &len, &new_num, sizeof(int), 2);

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}
```

### 3. Delete At

```c
int delete_at(void **arr, size_t *len, size_t element_size, size_t at_index);
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

int main() {
    size_t len = 4;
    int nums[] = {1, 2, 3, 4};

    delete_at((void **) &nums, &len, sizeof(int), 1);

    for (size_t i = 0; i < len; i++) {
        printf("%d ", nums[i]);
    }

    return 0;
}
```

### 4. Get

```c
void *get(void **arr, size_t len, size_t element_size, size_t at_index);
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

int main() {
    size_t len = 3;
    int nums[] = {10, 20, 30};

    int *result = (int *)get((void **) &nums, len, sizeof(int), 1);
    if (result) {
        printf("Value at index 1: %d\n", *result);
    }

    return 0;
}
```

#### Licence
This project is licensed under the MIT License - see the LICENSE file for details.

```bash
This `README.md` provides an overview of the functions, detailed documentation, and examples for how to use each function. You can expand it further based on more functions or specific needs in the project.
```
