#ifndef ACTION_H
#define ACTION_H

#include "array_op.h"
#include "person.h"
#include "stdio.h"

void get_people(person **people, size_t *len) {

  person n1 = {"Jane", 23};
  person n2 = {"Jenny", 24};
  person n3 = {"John", 25};
  person n4 = {"James", 26};

  insert((void **)people, len, &n1, sizeof(person));
  insert((void **)people, len, &n2, sizeof(person));
  insert((void **)people, len, &n3, sizeof(person));
  insert((void **)people, len, &n4, sizeof(person));
}

#endif