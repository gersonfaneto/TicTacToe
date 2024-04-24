#include "common/termctl.h"

#include <stdarg.h>
#include <stdio.h>
#include <termios.h>

#include "common/types.h"

void set_cursor(i32_t x, i32_t y) {
  printf("\033[%d;%dH", y, x);
}

void printf_at_xy(int x, int y, const char *format, ...) {
  va_list args;

  va_start(args, format);

  printf("\033[%d;%dH", y, x);

  vprintf(format, args);

  va_end(args);
}

void printf_at_rw(int row, int column, const char *format, ...) {
  va_list args;

  va_start(args, format);

  printf("\033[%d;%dH", row, column);

  vprintf(format, args);

  va_end(args);
}

void clear_screen(void) {
  printf("\033[H\033[2J\033[3J");
}

void disable_cursor(void) {
  printf("\033[?25l");
}

void enable_cursor(void) {
  printf("\033[?25h");
}

void enter_alt_screen(void) {
  printf("\033[?1049h\033[H");
}
void exit_alt_screen(void) {
  printf("\033[?1049l");
}

void enable_echo(void) {
  struct termios term = {0};

  tcgetattr(1, &term);

  term.c_lflag |= ECHO;

  tcsetattr(1, TCSANOW, &term);
}

void disable_echo(void) {
  struct termios term = {0};

  tcgetattr(1, &term);

  term.c_lflag &= ~ECHO;

  tcsetattr(1, TCSANOW, &term);
}
