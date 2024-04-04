#include "format.h"

#include <stdarg.h>
#include <stdio.h>

int println(const char* __restrict format, ...) {
  int lenght = 0;

  va_list args = {0};

  va_start(args, format);

  lenght += vprintf(format, args);
  lenght += printf("\n");

  va_end(args);

  return lenght;
}
