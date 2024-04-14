#include <stdio.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"

state_t state;

int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  state.mouse.x = state.window.cols / 2;
  state.mouse.y = state.window.rows / 2;

  set_handlers();

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  while (state.is_running) {
    clear_screen();

    printf_at_xy(0, 1, "Canvas :: [%d, %d]", state.window.cols, state.window.rows);
    printf_at_xy(0, 2, "Mouse  :: [%d, %d]", state.mouse.x, state.mouse.y);
    printf_at_xy(0, 3, "Clicks :: [%d, %d, %d]", state.mouse.left, state.mouse.middle, state.mouse.right);

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
