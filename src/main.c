#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"
#include "utils/ui.h"


#define PLAYER_X 0
#define PLAYER_Y 1

#define PLAYER_COMPONET_WIDTH 7 //largura
#define PLAYER_COMPONET_HEIGHT 5 //altura


/*const char* players[][PLAYER_COMPONET_HEIGHT] = {
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
};*/

state_t state;

int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  state.mouse.x = state.window.cols / 2;
  state.mouse.y = state.window.rows / 2;

  int camp_width = PLAYER_COMPONET_WIDTH + 4;
  int camp_heigth = PLAYER_COMPONET_HEIGHT + 2;

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

    /*for (int i = 0; i < PLAYER_COMPONET_HEIGHT; ++i) {
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
    }*/

    //Posição da 1ª coluna
    int position_column1 = (state.window.cols/2) - (camp_width*1.5);

    //Posição da 2ª coluna
    int position_column2 = (state.window.cols/2) - (camp_width*0.5);

    //Posição da 3ª coluna
    int position_column3 = (state.window.cols/2) + (camp_width*0.5);

    //Posição da 4ª coluna
    int position_column4 = (state.window.cols/2) + (camp_width*1.5);

    printf_at_xy(0, 4, "%d", position_column1);
    printf_at_xy(0, 5, "%d", position_column2);
    printf_at_xy(0, 6, "%d", position_column3);
    printf_at_xy(0, 7, "%d", position_column4);

    //Posição da 1ª linha
    int position_row1 = (state.window.rows/2) - (camp_heigth*1.5);

    //Posição da 2° linha
    int position_row2 = (state.window.rows/2) - (camp_heigth*0.5);

    //Posição da 3ª coluna
    int position_row3 = (state.window.rows/2) + (camp_heigth*0.5);

    //Posição da 4ª coluna
    int position_row4 = (state.window.rows/2) + (camp_heigth*1.5);

    printf_at_xy(0, 8, "%d", position_row1);
    printf_at_xy(0, 9, "%d", position_row2);
    printf_at_xy(0, 10, "%d", position_row3);
    printf_at_xy(0, 11, "%d", position_row4);

    printf_at_xy((state.window.cols/2) - (camp_width*1.5), (state.window.rows/2) - (camp_heigth*1.5), "1");
    printf_at_xy((state.window.cols/2) - (camp_width*0.5), (state.window.rows/2) - (camp_heigth*1.5), "2");
    printf_at_xy((state.window.cols/2) + (camp_width*0.5), (state.window.rows/2) - (camp_heigth*1.5), "3");
    printf_at_xy((state.window.cols/2) + (camp_width*1.5), (state.window.rows/2) - (camp_heigth*1.5), "4");

    printf_at_xy((state.window.cols/2) - (camp_width*1.5), (state.window.rows/2) - (camp_heigth*0.5), "5");
    printf_at_xy((state.window.cols/2) - (camp_width*0.5), (state.window.rows/2) - (camp_heigth*0.5), "6");
    printf_at_xy((state.window.cols/2) + (camp_width*0.5), (state.window.rows/2) - (camp_heigth*0.5), "7");
    printf_at_xy((state.window.cols/2) + (camp_width*1.5), (state.window.rows/2) - (camp_heigth*0.5), "8");

    printf_at_xy((state.window.cols/2) - (camp_width*1.5), (state.window.rows/2) + (camp_heigth*0.5), "9");
    printf_at_xy((state.window.cols/2) - (camp_width*0.5), (state.window.rows/2) + (camp_heigth*0.5), "10");
    printf_at_xy((state.window.cols/2) + (camp_width*0.5), (state.window.rows/2) + (camp_heigth*0.5), "11");
    printf_at_xy((state.window.cols/2) + (camp_width*1.5), (state.window.rows/2) + (camp_heigth*0.5), "12");

    printf_at_xy((state.window.cols/2) - (camp_width*1.5), (state.window.rows/2) + (camp_heigth*1.5), "13");
    printf_at_xy((state.window.cols/2) - (camp_width*0.5), (state.window.rows/2) + (camp_heigth*1.5), "14");
    printf_at_xy((state.window.cols/2) + (camp_width*0.5), (state.window.rows/2) + (camp_heigth*1.5), "15");
    printf_at_xy((state.window.cols/2) + (camp_width*1.5), (state.window.rows/2) + (camp_heigth*1.5), "16");

    if (state.mouse.x >= position_column1 && state.mouse.x <= position_column2) {

      if (state.mouse.y >= position_row1 && state.mouse.y <= position_row2) {
        printf_at_xy(0, 13, "quadrate 1");
      } else if (state.mouse.y > position_row2 && state.mouse.y <= position_row3) {
        printf_at_xy(0, 13, "quadrate 4");
      } else if (state.mouse.y > position_row3 && state.mouse.y <= position_row4) {
        printf_at_xy(0, 13, "quadrate 7");
      }

    } else if (state.mouse.x > position_column2 && state.mouse.x <= position_column3) {
      
      if (state.mouse.y >= position_row1 && state.mouse.y <= position_row2) {
        printf_at_xy(0, 13, "quadrate 2");
      } else if (state.mouse.y > position_row2 && state.mouse.y <= position_row3) {
        printf_at_xy(0, 13, "quadrate 5");
      } else if (state.mouse.y > position_row3 && state.mouse.y <= position_row4) {
        printf_at_xy(0, 13, "quadrate 8");
      }

    } else if (state.mouse.x > position_column3 && state.mouse.x <= position_column4) {
      
      if (state.mouse.y >= position_row1 && state.mouse.y <= position_row2) {
        printf_at_xy(0, 13, "quadrate 3");
      } else if (state.mouse.y > position_row2 && state.mouse.y <= position_row3) {
        printf_at_xy(0, 13, "quadrate 6");
      } else if (state.mouse.y > position_row3 && state.mouse.y <= position_row4) {
        printf_at_xy(0, 13, "quadrate 9");
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
