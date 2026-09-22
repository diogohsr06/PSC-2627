#include <stdio.h>

unsigned getbits(unsigned value, unsigned pos, unsigned n) {
  return (value >> pos) & ((1 << n) - 1);
}

int main() {
  unsigned x = 0xE7BA896C;
  unsigned v1 = getbits(x, 3, 6);
  unsigned v2 = getbits(x, 6, 2);
  unsigned v3 = getbits(x, 12, 5);
  unsigned v4 = getbits(x, 29, 3);
  printf("v1: %x\n", v1);
  printf("v2: %x\n", v2);
  printf("v3: %x\n", v3);
  printf("v4: %x\n", v4);
  return 0;
}




