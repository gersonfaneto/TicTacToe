#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"
//#include "app/mouse.h"
#include "app/appearance.h"

state_t state;
board_t board;

int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  set_handlers();

  printf("Starting...\n");

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  i8_t quadrant[2];
  board = init_board();

  while (state.is_running) {
    clear_screen();

    printf_at_xy(0, 1, "Canvas :: [%d, %d]", state.window.cols, state.window.rows);
    printf_at_xy(0, 2, "Mouse  :: [%d, %d]", state.mouse.x, state.mouse.y);
    printf_at_xy(0, 3, "Clicks :: [%d, %d, %d]", state.mouse.left, state.mouse.middle, state.mouse.right);

    quadrant[2] = get_mouse(state.mouse.x, state.mouse.y, board);

    printf_at_xy(state.mouse.x, state.mouse.y, "%c\n", '@');

    state.mouse.read(&state.mouse, state.window.rows, state.window.cols);
  }

  exit_alt_screen();
  enable_cursor();
  enable_echo();

  close(state.mouse.fd);

  printf("Closing...\n");

  return 0;
}