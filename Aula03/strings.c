#include <stdio.h>

unsigned xstrlen(char * str) {
  unsigned len = 0;
  unsigned i;
  for (i = 0; *(str + i) != '\0'; ++i) {
    ++len;
  }
  return len;
}

int main() {
  char *str1 = "Hello!";
  char *str2 = "LEIC32D";
  unsigned len1 = xstrlen(str1);
  unsigned len2 = xstrlen(str2);
  printf("strlen(str1) = %d\n", len1);
  printf("strlen(str2) = %d\n", len2);
}
