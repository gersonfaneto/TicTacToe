#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "common/termctl.h"
#include "state.h"
#include "app/appearance.h"
#include "common/algorithm.h"

state_t state;
board_t board;

int main(void) {

  init_game(&board);
  
  i8_t* coordinates;

  char current_player = 'X';
  
  i8_t state_game = 0;
  i8_t free_position;
  i8_t win;
  i8_t out_of_board = 0;
  i8_t invalid_position = 0;
  i8_t change_board = 0;
  i8_t signal_retry = 0;

  while (state.is_running) {

    if(state_game == 0) {
      win = 0;
      current_player = 'X';
      board = init_board();
      change_state(&state_game, &state.mouse.right);
    }
    else if (state_game == 1) {

      coordinates = get_mouse(state.mouse.x, state.mouse.y, board); //Função que retorna o endereço de memória da array
      free_position = is_empty(board, *coordinates, *(coordinates + 1));

      if(!win) {

        if(*coordinates == -1 && state.mouse.left) {
          out_of_board = 1;
          invalid_position = 0;
        }
        else if(*coordinates != -1 && state.mouse.left) {
          out_of_board = 0;
          if(!free_position) {
            invalid_position = 1;
          }
          else {
            invalid_position = 0;
            if(current_player == 'X') {

              board.matrix[*coordinates][*(coordinates + 1)] = 'X';
              change_board = 1;
              win = check_win(board, DIMENSION, 'X');
              current_player = 'O';

            }
            else {

              board.matrix[*coordinates][*(coordinates + 1)] = 'O';
              change_board = 1;
              win = check_win(board, DIMENSION, 'O');
              current_player = 'X';

            }
            win = check_tie(board, DIMENSION) ? 1 : win;
          }
        }
      }
      change_state(&state_game, &state.mouse.right);
    }

    clear_screen();

    if(state_game == 0) {
      init_message();
    }
    else {
      show_contour(DIMENSION, board);
      if(out_of_board) {
        out_of_board_error();
      }
      if(invalid_position) {
        invalid_position_error();
      }
      if(change_board) {
        show_board(DIMENSION, board);
      }

      if(check_tie(board, DIMENSION)) {
        show_tie();
        retry_message();
      }
      else {
        if(win && current_player == 'O') {
          show_victory_X();
          retry_message();
        }
        else if(win && current_player == 'X') {
          show_victory_O();
          retry_message();
        }
        else {
          show_players(current_player);
        }
      }
    }
    
    print_mouse();
  }

  close_game();
}
