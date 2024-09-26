#ifndef MAIN_H
#define MAIN_H

#include "action.h"
#include "person.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exec() {
  person *pp = NULL;
  size_t len = 0;

  get_people(&pp, &len);

  person p1 = {"Jeff", 22};

  size_t i = 3;

  int n = insert_at((void **)&pp, &len, &p1, sizeof(person), i);
  if (n != 0)
    return;

  n = delete_at((void **)&pp, &len, sizeof(person), i);
  if (n != 0)
    return;

  person_for_each(pp, len, person_print);

  free(pp);
}

#endif // MAIN_H