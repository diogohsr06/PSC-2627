/*
Programe a função mini_snprintf segundo a definição da função sprintf da
biblioteca normalizada da linguagem C, limitada aos especificadores de conversão
c, s, d, x e f, sem adornos. Na programação desta função não deve utilizar a
função sprintf. Consulte o exemplo da secção 7.3 do livro The C Programming
Language. O texto produzido é depositado num array de caracteres, nas condições
definidas no exercício 1. A função retorna a dimensão da string produzida ou
zero no caso da dimensão do array não ser suficiente.
*/

#include <stdio.h>
size_t mini_snprintf(char *buffer, size_t buffer_size, const char *format,
                     ...) {}
