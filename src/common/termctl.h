#ifndef TERMCTL_H_
#define TERMCTL_H_

#include "common/types.h"

/**
 * All the declarations on this file, and their respective implementations, rely
 * on ANSI Escape Sequences.
 *
 * See :: https://en.wikipedia.org/wiki/ANSI_escape_code
 */

/**
 * Colors for the text - foreground.
 */
#define TC_NRM "\x1B[0m"
#define TC_RED "\x1B[1;31m"
#define TC_GRN "\x1B[1;32m"
#define TC_YEL "\x1B[1;33m"
#define TC_BLU "\x1B[1;34m"
#define TC_MAG "\x1B[1;35m"
#define TC_CYN "\x1B[1;36m"
#define TC_WHT "\x1B[1;37m"

/**
 * Colors for the text (brighter version) - foreground.
 */
#define TC_B_NRM "\x1B[0m"
#define TC_B_RED "\x1B[0;31m"
#define TC_B_GRN "\x1B[0;32m"
#define TC_B_YEL "\x1B[0;33m"
#define TC_B_BLU "\x1B[0;34m"
#define TC_B_MAG "\x1B[0;35m"
#define TC_B_CYN "\x1B[0;36m"
#define TC_B_WHT "\x1B[0;37m"

/**
 * Colors for the window - background.
 */
#define TC_BG_NRM "\x1B[40m"
#define TC_BG_RED " \x1B[41m"
#define TC_BG_GRN "\x1B[42m"
#define TC_BG_YEL "\x1B[43m"
#define TC_BG_BLU "\x1B[44m"
#define TC_BG_MAG "\x1B[45m"
#define TC_BG_CYN "\x1B[46m"
#define TC_BG_WHT "\x1B[47m"

/**
 * @brief Moves the cursor to a specific position on the terminal.
 *
 * @param[in] x The desired X position on the terminal.
 * @param[in] y The desired Y position on the terminal.
 */
void set_cursor(i32_t x, i32_t y);

/**
 * @brief Prints a `format` under a specific position on the terminal. Various
 * arguments may be provided after `format`, respecting the rules present on
 * `printf` (used on the underlying implementation).
 *
 * @param[in] row The desired row on the terminal.
 * @param[in] column The desired column on the terminal.
 * @param[in] format The `char *` to be printed.
 */
void printf_at_rw(i32_t row, i32_t column, const char* __restrict format, ...);

/**
 * @brief Prints a `format` under a specific position on the terminal. Various
 * arguments may be provided after `format`, respecting the rules present on
 * `printf` (used on the underlying implementation).
 *
 * @param[in] x The desired X position on the terminal.
 * @param[in] y The desired Y position on the terminal.
 * @param[in] format The `char *` to be printed.
 */
void printf_at_xy(i32_t x, i32_t y, const char* __restrict format, ...);

/**
 * @brief Clears all the text on the terminal.
 */
void clear_screen(void);

/**
 * @brief Enables back the cursor, MUST be executed at the end of the game
 * to restore the terminal to its default state.
 */
void enable_cursor(void);

/**
 * @brief Disables the cursor, as it may be distracting when printing/rendering
 * the text on the terminal.
 */
void disable_cursor(void);

/**
 * @brief Enters the alternative screen, useful to preserve the state of the
 * terminal when the game starts.
 */
void enter_alt_screen(void);

/**
 * @brief Exits the alternative screen, MUST be executed at the end of the game
 * to restore the terminal to its default state.
 */
void exit_alt_screen(void);

/**
 * @brief Enables the "echo" functionality, MUST be executed at the end of the
 * game to restore the terminal to its default state.
 */
void enable_echo(void);

/**
 * @brief Disabled the "echo" functionality, block the terminal from capturing
 * characters typed by the user during the execution of the game.
 */
void disable_echo(void);

#endif  // !TERMCTL_H_
