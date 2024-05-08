#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "app/handlers.h"
#include "common/termctl.h"
#include "state.h"
#include "app/appearance.h"
#include "common/algorithm.h"

state_t state;
board_t board;

/*
int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  i8_t* coordinates; //armazena o endereço do array com as coordenadas
  board = init_board();

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

    coordinates = get_mouse(state.mouse.x, state.mouse.y, board); //Função que retorna o endereço de memória da array
    //show_board(DIMENSION, board);

    //printf_at_xy(0, 4, "[%d, %d]", *coordinates, *(coordinates + 1));
    printf_at_xy(0, 5, "%c, %c, %c\n%c, %c, %c\n%c, %c, %c", board.matrix[0][0], board.matrix[0][1], board.matrix[0][2], board.matrix[1][0], board.matrix[1][1], board.matrix[1][2], board.matrix[2][0], board.matrix[2][1], board.matrix[2][2]);

    run_game(&board, 9, coordinates);

    printf_at_xy(0, 10, "%c, %c, %c\n%c, %c, %c\n%c, %c, %c", board.matrix[0][0], board.matrix[0][1], board.matrix[0][2], board.matrix[1][0], board.matrix[1][1], board.matrix[1][2], board.matrix[2][0], board.matrix[2][1], board.matrix[2][2]);
    show_board(DIMENSION, board);

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
*/

int main(void) {
  state.is_running = 1;

  state.mouse = init_mouse();
  state.window = init_window();

  i8_t* coordinates; //armazena o endereço do array com as coordenadas
  board = init_board();

  set_handlers();

  printf("Starting...\n");

  enter_alt_screen();
  disable_cursor();
  disable_echo();

  char current_player = 'X';

  i8_t free_position;

  i8_t win;

  while (state.is_running) {
    clear_screen();

    coordinates = get_mouse(state.mouse.x, state.mouse.y, board); //Função que retorna o endereço de memória da array
    free_position = is_empty(board, *coordinates, *(coordinates + 1));

    if(!win) {
      if(current_player == 'X') {
        if(*coordinates == -1 && state.mouse.left) {
          //Selecione uma posição dentro do tabuleiro
        }
        else if(*coordinates != -1 && state.mouse.left) {
          if(free_position) {
            board.matrix[*coordinates][*(coordinates + 1)] = 'X';
            win = check_win(&board, DIMENSION, 'X');
            current_player = 'O';
          }
          else {
            //Escolha uma casa livre
          }
        }
      }
      else {
        if(*coordinates == -1 && state.mouse.left) {
          //Selecione uma posição dentro do tabuleiro
        }
        else if(*coordinates != -1 && state.mouse.left) {
          if(free_position) {
            board.matrix[*coordinates][*(coordinates + 1)] = 'O';
            win = check_win(&board, DIMENSION, 'O');
            current_player = 'X';
          }
          else {
            //Escolha uma casa livre
          }
        }
      }
    }  

    printf_at_xy(0, 0, "win: %d", win);
    //run_game(&board, 9, coordinates);

    printf_at_xy(0, 10, "%c, %c, %c\n%c, %c, %c\n%c, %c, %c", board.matrix[0][0], board.matrix[0][1], board.matrix[0][2], board.matrix[1][0], board.matrix[1][1], board.matrix[1][2], board.matrix[2][0], board.matrix[2][1], board.matrix[2][2]);
    show_board(DIMENSION, board);


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