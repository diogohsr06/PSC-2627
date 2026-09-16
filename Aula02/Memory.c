#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 256

struct Student {
  unsigned int number;
  char name [NAME_LEN];
};

struct Student s = { 1234, "Pedro" };

struct Student *ps = &s;

void f(int i) {
  struct Student ls = { 1234 + i, "Pedro" };
  printf("local student at: 0x%p\n", &ls);
  struct Student *ps = malloc(sizeof(struct Student));
  printf("dynamic student at: 0x%p\n", &ps);
  if (i > 0) {
    f(i - 1);
  }
  printf("local student at: 0x%p\n", &ls);
}

int main() {
  printf("global student at: 0x%p\n", &s);
  f(2);
  return 0;
}
