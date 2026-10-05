#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

size_t float_to_string(float value, char buffer[], size_t buffer_size) {
  uint32_t bits;
  memcpy(&bits, &value, sizeof(bits));

  /* Extract IEEE-754 fields */
  uint32_t sign = bits >> 31;
  uint32_t exponent_bits = (bits >> 23) & 0xff;
  uint32_t mantissa = bits & 0x7fffff;

  /* Handle zero */
  if (exponent_bits == 0 && mantissa == 0) {
    if (buffer_size < 9)
      return 0;
    if (sign)
      buffer[0] = '-';
    buffer[sign ? 1 : 0] = '0';
    buffer[sign ? 2 : 1] = '.';
    for (int i = 0; i < 6; i++)
      buffer[(sign ? 3 : 2) + i] = '0';
    buffer[(sign ? 9 : 8)] = '\0';
    return sign ? 9 : 8;
  }

  /*
   * For normal numbers, add the implicit leading 1.
   */
  uint32_t significand = mantissa | (1u << 23);
  int exponent = (int)exponent_bits - 127;

  /*
   * Calculate value * 1,000,000
   * using integer arithmetic only.
   */
  __uint128_t scaled;
  if (exponent >= 23) {
    scaled = (__uint128_t)significand << (exponent - 23);
    scaled *= 1000000u;
  } else {
    scaled = (__uint128_t)significand * 1000000u;
    int shift = 23 - exponent;

    /*
     * Round to nearest integer.
     */
    if (shift > 0) {
      scaled >>= shift;
    }
  }

  /*
   * Separate integer and fractional parts.
   */
  __uint128_t integer_part = scaled / 1000000u;
  uint32_t fractional_part = (uint32_t)(scaled % 1000000u);

  /*
   * Convert integer part to decimal.
   */
  char temp[64];
  int i = 0;
  if (integer_part == 0) {
    temp[i++] = '0';
  } else {
    while (integer_part > 0) {
      temp[i++] = '0' + (integer_part % 10);
      integer_part /= 10;
    }
  }

  /*
   * Number of characters:
   * sign + integer + '.' + 6 decimals + '\0'
   */
  size_t integer_length = (size_t)i;
  size_t total_length = (sign ? 1 : 0) + integer_length + 1 + 6;
  if (total_length + 1 > buffer_size)
    return 0;
  size_t pos = 0;
  if (sign)
    buffer[pos++] = '-';

  /*
   * Reverse integer digits.
   */
  while (i > 0)
    buffer[pos++] = temp[--i];
  buffer[pos++] = '.';

  /*
   * Write exactly six decimal digits.
   */
  uint32_t divisor = 100000;
  for (int j = 0; j < 6; j++) {
    buffer[pos++] = '0' + (fractional_part / divisor) % 10;
    divisor /= 10;
  }
  buffer[pos] = '\0';
  return pos;
}
