/*
Programe a função time_to_string que converte a informação de calendário,
recebida no parâmetro tm, ponteiro para uma struct do tipo struct tm , para uma
representação em texto, no formato “ww, dd‐mm‐yyyy,1 hh:mm:ss”. Por exemplo:
”segunda-feira, 14-09-2026, 08:12:30”. O texto produzido é depositado num array
de caracteres, nas condições definidas no exercício 1. A função retorna a
dimensão da string produzida ou zero no caso da dimensão do array não ser
suficiente. (Os caracteres com acento ou o ‘ç’ ocupam dois bytes na codificação
UTF-8.)
*/

#include <stdio.h>

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
};

size_t time_to_string(struct tm *tm, char *buffer, size_t buffer_size) { TODO }
