#include <stdio.h>

/*
  * Programe a função int_to_string que representa em texto, na base de
numeração base (considere apenas as bases 2, 8, 10 e 16), o valor inteiro
recebido em value. O texto é depositado no array de caracteres indicado pelo
ponteiro buffer, no formato de string C. O parâmetro buffer_size indica a
dimensão desse array. A função retorna a dimensão da string produzida ou zero no
caso da dimensão do array não ser suficiente. As representações nas bases 2, 8 e
16 devem ser prefixadas com as respectivas notações.
*/
size_t int_to_string(unsigned value, int base, char buffer[],
                     size_t buffer_size) {
  // Declaration of variables to be used;
  // prefix stores the number of characters of the prefix;
  // digits - an array which includes all the digits used by the 4 bases;
  // temp - Temporary array to store digits (least significant to most
  // significant); i = temp's counter.
  int prefix;
  char digits[] = "0123456789abcdef";
  char temp[32];
  int i = 0;

  // Checks base and returns corresponding prefix size;
  // An invalid base ends with exit code 0.
  switch (base) {
  case 2:
    prefix = 2;
    break;
  case 8:
    prefix = 1;
    break;
  case 10:
    prefix = 0;
    break;
  case 16:
    prefix = 2;
    break;
  default:
    return 0;
  }

  // Number convertion
  // If value is 0, the 0 digit is added to temp
  // value % base - position of the current digit
  // value /= base - new value to calculate next digit to be added
  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = digits[value % base];
      value /= base;
    }
  }

  // Verifies if buffer is big enough to store
  if ((size_t)(prefix + i + 1) > buffer_size)
    return 0;

  // Writes in buffer the prefix characters before temp's digits
  switch (base) {
  case 2:
    buffer[0] = '0';
    buffer[1] = 'b';
    break;
  case 8:
    buffer[0] = '0';
    break;
  case 16:
    buffer[0] = '0';
    buffer[1] = 'x';
    break;
  }

  // Copies inverted temp's content to buffer;
  // Returns its lenght. Buffer's size = prefix + i (temp's size)
  for (int j = 0; j < i; j++) {
    buffer[prefix + j] = temp[i - 1 - j];
  }
  buffer[prefix + i] = '\0';

  return (size_t)(prefix + i);
}
