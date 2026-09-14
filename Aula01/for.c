#include <stdio.h>

int main() {
  int tc;

  for (tc = -5; tc < 55; tc += 5) {
    int tf = 9.0/5 * tc + 32;\
    printf("%d C => %d F\n", tc, tf);
  }
  return 0;
}
