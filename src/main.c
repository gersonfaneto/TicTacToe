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

  i8_t out_of_board = 0;
  i8_t invalid_posicion = 0;

  while (state.is_running) {
    clear_screen();

    coordinates = get_mouse(state.mouse.x, state.mouse.y, board); //Função que retorna o endereço de memória da array
    free_position = is_empty(board, *coordinates, *(coordinates + 1));

    if(!win) {

      if(*coordinates == -1 && state.mouse.left) {
        out_of_board = 1;
        invalid_posicion = 0;
      }
      else if(*coordinates != -1 && state.mouse.left) {
        out_of_board = 0;
        if(!free_position) {
          invalid_posicion = 1;
        }
        else {
          invalid_posicion = 0;
          if(current_player == 'X') {

            board.matrix[*coordinates][*(coordinates + 1)] = 'X';
            win = check_win(board, DIMENSION, 'X');
            current_player = 'O';

          }
          else {

            board.matrix[*coordinates][*(coordinates + 1)] = 'O';
            win = check_win(board, DIMENSION, 'O');
            current_player = 'X';

          }
          win = check_tie(board, DIMENSION) ? 1 : win;
        }
      }
    }

    if(out_of_board) {
      out_of_board_error(board);
    }

    if(invalid_posicion) {
      invalid_posicion_error(board);
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