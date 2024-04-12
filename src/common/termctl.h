#ifndef TERMCTL_H_
#define TERMCTL_H_

#include "common/types.h"

#define TC_NRM "\x1B[0m"
#define TC_RED "\x1B[1;31m"
#define TC_GRN "\x1B[1;32m"
#define TC_YEL "\x1B[1;33m"
#define TC_BLU "\x1B[1;34m"
#define TC_MAG "\x1B[1;35m"
#define TC_CYN "\x1B[1;36m"
#define TC_WHT "\x1B[1;37m"

#define TC_B_NRM "\x1B[0m"
#define TC_B_RED "\x1B[0;31m"
#define TC_B_GRN "\x1B[0;32m"
#define TC_B_YEL "\x1B[0;33m"
#define TC_B_BLU "\x1B[0;34m"
#define TC_B_MAG "\x1B[0;35m"
#define TC_B_CYN "\x1B[0;36m"
#define TC_B_WHT "\x1B[0;37m"

#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED " \x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"

void set_cursor(i32_t x, i32_t y);

void printf_at_rw(i32_t row, i32_t column, const char* __restrict format, ...);

void printf_at_xy(i32_t x, i32_t y, const char* __restrict format, ...);

void clear_screen(void);

void enable_cursor(void);

void disable_cursor(void);

void enter_alt_screen(void);

void exit_alt_screen(void);

void enable_echo(void);

void disable_echo(void);

#endif  // !TERMCTL_H_
