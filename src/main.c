#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"

#define PLAYER_X 0
#define PLAYER_Y 1

#define PLAYER_COMPONET_WIDTH 7
#define PLAYER_COMPONET_HEIGHT 5

const char* players[][PLAYER_COMPONET_HEIGHT] = {
    {
        "  ___  ",
        " / _ \\ ",
        "| | | |",
        "| |_| |",
        " \\___/ ",
    },
    {
        "__  __ ",
        "\\ \\/ / ",
        " \\  /  ",
        " /  \\  ",
        "/_/\\_\\ ",
    },
};

state_t state;

int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  state.mouse.x = state.window.cols / 2;
  state.mouse.y = state.window.rows / 2;

  set_handlers();

  printf("Starting...\n");

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  while (state.is_running) {
    clear_screen();

    printf_at_xy(0, 1, "Canvas :: [%d, %d]", state.window.cols, state.window.rows);
    printf_at_xy(0, 2, "Mouse  :: [%d, %d]", state.mouse.x, state.mouse.y);
    printf_at_xy(0, 3, "Clicks :: [%d, %d, %d]", state.mouse.left, state.mouse.middle, state.mouse.right);

    for (int i = 0; i < PLAYER_COMPONET_HEIGHT; ++i) {
      if (state.mouse.left) {
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_X][i]) / 2) - strlen(players[PLAYER_Y][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_X][i]);
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_Y][i]) / 2) + strlen(players[PLAYER_X][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_Y][i]);
      } else {
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_Y][i]) / 2) - strlen(players[PLAYER_X][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_Y][i]);
        printf_at_xy(((state.window.cols / 2) - (strlen(players[PLAYER_X][i]) / 2) + strlen(players[PLAYER_Y][i])),
                     state.window.rows / 2 + i, "%s", players[PLAYER_X][i]);
      }
    }

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
