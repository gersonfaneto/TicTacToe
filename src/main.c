#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include "app/mouse.h"
#include "app/window.h"
#include "common/termctl.h"

volatile i32_t is_running = 1;

void interruption_handler(i32_t signal);

int main(void) {
  mouse_t mouse;
  window_t window;

  window = init_window();

  mouse = init_mouse(window.cols, window.rows);

  signal(SIGINT, interruption_handler);

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  mouse.x = window.cols / 2;
  mouse.y = window.rows / 2;

  while (is_running) {
    clear_screen();

    printf_at_xy(0, 1, "Canvas :: [%d, %d]", window.cols, window.rows);
    printf_at_xy(0, 2, "Mouse  :: [%d, %d]", mouse.x, mouse.y);
    printf_at_xy(0, 3, "Clicks :: [%d, %d, %d]", mouse.left, mouse.middle,
                 mouse.right);

    printf_at_xy(mouse.x, mouse.y, "%c\n", '@');

    mouse.read(&mouse, window.rows, window.cols);
  }

  exit_alt_screen();
  enable_cursor();
  enable_echo();

  close(mouse.fd);

  printf("Closing...\n");

  return 0;
}

void interruption_handler(i32_t signal) { is_running = 0; }
