#ifndef PERSON_H
#define PERSON_H

#include <stdio.h>

typedef struct person {
  const char *name;
  int age;
} person;

void person_print(person p) {
  printf("{name: \"%s\", age: %d} \n", p.name, p.age);
}

void person_for_each(person *arr, size_t len, void (*func)(person)) {
  person *index = (person *)arr;
  while (index != ((person *)arr + len)) {
    func(*index);
    index++;
  }
}

#endif