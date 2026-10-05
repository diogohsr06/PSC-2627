/*
 *	Programação em Sistemas Computacionais
 *	Semestre de inverno de 2026/2027
 *	Primeira série de exercícios
 *
 *	Programa de teste do 3º exercício
 *
 *	Utilização:
 *
 *	$ gcc mini_snprintf_test.c mini_snprintf.c ../exercicio1/int_to_string.c
 * ../exercicio2/float_to_string.c -o mini_snprint
 *
 *	$ ./mini_snprintf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

int mini_snprintf(char *buffer, size_t buffer_size, const char *format, ...);

union values {
  int i;
  float f;
  char c;
  char *s;
};

struct {
  char buffer[20];
  size_t buffer_size;
  char *format;
  union values values[4];
  size_t result_size;
  char *result_string;
} test_array[] = {
    {.buffer_size = 2,
     .format = "%d",
     .values = {{2}},
     .result_size = 1,
     .result_string = "2"},
    {.buffer_size = 4,
     .format = "%d %c",
     .values = {{2}, {'a'}},
     .result_size = 3,
     .result_string = "2 a"},
    {.buffer_size = 13,
     .format = "aa %x bb %s",
     .values = {{10}, {.s = "YY"}},
     .result_size = 12,
     .result_string = "aa 0xa bb YY"},
    {.buffer_size = 4,
     .format = "%d %c",
     .values = {{2}, {'a'}},
     .result_size = 3,
     .result_string = "2 a"},

    /* Testes envolvendo floats */
    {.buffer_size = 9,
     .format = "%f",
     .values = {[0].f = 3.5},
     .result_size = 8,
     .result_string = "3.500000"},
    {.buffer_size = 13,
     .format = "%s %f",
     .values = {[0].s = "aaa", [1].f = 4.4},
     .result_size = 12,
     .result_string = "aaa 4.400000"},
};

int exit_code = EXIT_SUCCESS;

void print_result(int i, size_t result_size) {
  if (result_size != test_array[i].result_size) {
    printf("[%d] - Error, expected size = %zd, returned size = %zd\n", i,
           test_array[i].result_size, result_size);
    exit_code = EXIT_FAILURE;
    ;
  } else if (result_size > 0 &&
             strcmp(test_array[i].buffer, test_array[i].result_string) != 0) {
    printf("[%d] - Error, expected string = %s, returned string = %s\n", i,
           test_array[i].result_string, test_array[i].buffer);
    exit_code = EXIT_FAILURE;
  } else {
    printf("[%d] - OK\n", i);
  }
}

int main() {
  size_t i;
  size_t return_value;
  for (i = 0; i < ARRAY_SIZE(test_array) - 2; ++i) {
    return_value = mini_snprintf(
        test_array[i].buffer, test_array[i].buffer_size, test_array[i].format,
        test_array[i].values[0], test_array[i].values[1],
        test_array[i].values[2], test_array[i].values[3]);
    print_result(i, return_value);
  }

  i = ARRAY_SIZE(test_array) - 2;
  return_value = mini_snprintf(test_array[i].buffer, test_array[i].buffer_size,
                               test_array[i].format, test_array[i].values[0].f,
                               test_array[i].values[1]);
  print_result(i, return_value);

  i = ARRAY_SIZE(test_array) - 1;
  return_value = mini_snprintf(test_array[i].buffer, test_array[i].buffer_size,
                               test_array[i].format, test_array[i].values[0],
                               test_array[i].values[1].f);
  print_result(i, return_value);

  return exit_code;
}
