#include <stdio.h>

/*
  * Programe a função int_to_string que representa em texto, na base de numeração base (considere apenas
as bases 2, 8, 10 e 16), o valor inteiro recebido em value. O texto é depositado no array de caracteres
indicado pelo ponteiro buffer, no formato de string C. O parâmetro buffer_size indica a dimensão desse
array. A função retorna a dimensão da string produzida ou zero no caso da dimensão do array não ser
suficiente. As representações nas bases 2, 8 e 16 devem ser prefixadas com as respectivas notações.
*/
size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {
  int prefix;
  char digits[] = "0123456789abcdef";
  char temp[32];
  int i = 0;

  switch (base) {
    case 2:
      prefix = 2;
      break;
    case 8:
      prefix = 2;
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

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value > 0) {
      temp[i++] = digits[value % base];
      value /= base;
    }
  }

  if ((size_t)(prefix + i + 1) > buffer_size) return 0;

  switch (base) {
    case 2:
      buffer[0] = '0';
      buffer[1] = 'b';
      break;
    case 8:
      buffer[0] = '0';
      buffer[1] = 'o';
      break;
    case 16:
      buffer[0] = '0';
      buffer[1] = 'x';
      break;
  }

  for (int j = 0; j < i; j++) {
    buffer[prefix + j] = temp[i - 1 - j];
  }
  buffer[prefix + i] = '\0';

  return (size_t)(prefix + i);
}

int main() {
  int size = 10;
  char buffer[size];
  size_t len = int_to_string(10, 2, buffer, sizeof(buffer));
  printf("%s (len=%zu)\n", buffer, len);

  len = int_to_string(255, 16, buffer, sizeof(buffer));
  printf("%s (len=%zu)\n", buffer, len);

  len = int_to_string(0, 8, buffer, sizeof(buffer));
  printf("%s (len=%zu)\n", buffer, len);

  len = int_to_string(12345, 10, buffer, sizeof(buffer));
  printf("%s (len=%zu)\n", buffer, len);

  return 0;
}
