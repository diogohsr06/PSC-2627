#include <stdarg.h>
#include <stddef.h>
#include <string.h>

size_t float_to_string(float value, char buffer[], size_t buffer_size);

/*
 * Adds one character to the buffer.
 *
 * There must always be space for the terminating '\0'.
 */
static int addChar(char *buffer, size_t buffer_size, size_t *position, char c) {
  if (*position + 1 >= buffer_size)
    return 0;
  buffer[*position] = c;
  (*position)++;
  return 1;
}

/*
 * Adds a string to the buffer.
 */
static int addString(char *buffer, size_t buffer_size, size_t *position,
                     const char *str) {
  while (*str != '\0') {
    if (!addChar(buffer, buffer_size, position, *str))
      return 0;
    str++;
  }
  return 1;
}

/*
 * Adds an unsigned integer using the specified base.
 */
static int addUnsigned(char *buffer, size_t buffer_size, size_t *position,
                       unsigned int value, unsigned int base) {
  const char digits[] = "0123456789abcdef";
  char temp[32];
  size_t i = 0;
  if (value == 0)
    return addChar(buffer, buffer_size, position, '0');
  while (value > 0) {
    temp[i++] = digits[value % base];
    value /= base;
  }
  while (i > 0) {
    i--;
    if (!addChar(buffer, buffer_size, position, temp[i]))
      return 0;
  }
  return 1;
}

/*
 * Adds a signed integer in decimal.
 */
static int addInt(char *buffer, size_t buffer_size, size_t *position,
                  int value) {
  if (value < 0) {
    if (!addChar(buffer, buffer_size, position, '-'))
      return 0;
    /*
     * Avoid overflow when value is INT_MIN.
     */
    unsigned int magnitude = (unsigned int)(-(value + 1)) + 1;
    return addUnsigned(buffer, buffer_size, position, magnitude, 10);
  }
  return addUnsigned(buffer, buffer_size, position, (unsigned int)value, 10);
}

/*
 * Adds a hexadecimal number with the 0x prefix.
 */
static int addHex(char *buffer, size_t buffer_size, size_t *position,
                  unsigned int value) {
  if (!addChar(buffer, buffer_size, position, '0'))
    return 0;
  if (!addChar(buffer, buffer_size, position, 'x'))
    return 0;
  return addUnsigned(buffer, buffer_size, position, value, 16);
}

/*
 * Converts a float using float_to_string() and adds the resulting
 * string to the buffer.
 */
static int addFloat(char *buffer, size_t buffer_size, size_t *position,
                    float value) {
  char temp[64];
  size_t length = float_to_string(value, temp, sizeof(temp));
  if (length == 0)
    return 0;
  return addString(buffer, buffer_size, position, temp);
}

size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format,
                     ...) {
  size_t position = 0;
  if (buffer_size == 0)
    return 0;
  va_list args;
  va_start(args, format);

  while (*format != '\0') {
    /*
     * Normal character.
     */
    if (*format != '%') {
      if (!addChar(buffer, buffer_size, &position, *format)) {
        va_end(args);
        return 0;
      }
      format++;
      continue;
    }

    /*
     * Conversion specifier.
     */
    format++;
    switch (*format) {
    case 'c': {
      int value = va_arg(args, int);
      if (!addChar(buffer, buffer_size, &position, (char)value)) {
        va_end(args);
        return 0;
      }
      break;
    }
    case 's': {
      char *value = va_arg(args, char *);
      if (!addString(buffer, buffer_size, &position, value)) {
        va_end(args);
        return 0;
      }
      break;
    }
    case 'd': {
      int value = va_arg(args, int);
      if (!addInt(buffer, buffer_size, &position, value)) {
        va_end(args);
        return 0;
      }
      break;
    }
    case 'x': {
      unsigned int value = va_arg(args, unsigned int);
      if (!addHex(buffer, buffer_size, &position, value)) {
        va_end(args);
        return 0;
      }
      break;
    }
    case 'f': {
      double value = va_arg(args, double);
      if (!addFloat(buffer, buffer_size, &position, (float)value)) {
        va_end(args);
        return 0;
      }
      break;
    }
    default:
      va_end(args);
      return 0;
    }
    format++;
  }

  buffer[position] = '\0';
  va_end(args);
  return position;
}
