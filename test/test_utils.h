#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdlib.h>

typedef int (*func)();
int unexpected_error(const char *test_name);
int test_for_each(func tests[], size_t len);

#endif // TEST_UTILS_H