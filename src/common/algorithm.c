#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include "state.h"

/*
void init_matrix(board_t board, i8_t dimension) {
  for(i8_t i = 0; i < dimension; ++i) {
    for(i8_t j = 0; j < dimension; ++j) {
      board.matrix[i][j] = '-';
    }
  }
}*/

int is_empty(board_t board, i8_t row, i8_t column) {
  if (board.matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

int verify_rows(board_t board, i8_t dimension, char playerCharacther) {
  i8_t win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    for (i8_t j = 0; j < dimension; ++j) {
      if (board.matrix[i][j] != playerCharacther) {
        win = 0;
        break;
      }
    }
    if (win) {
      return 1;
    }
  }
  return 0;
}

int verify_columns(board_t board, i8_t dimension, char playerCharacther) {
  i8_t win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    for (i8_t j = 0; j < dimension; ++j) {
      if (board.matrix[j][i] != playerCharacther) {
        win = 0;
        break;
      }
    }
    if (win) {
      return 1;
    }
  }
  return 0;
}

int verify_main_diagonal(board_t board, i8_t dimension, char playerCharacther) {
  i8_t win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    if (board.matrix[i][i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

int verify_secundary_diagonal(board_t board, i8_t dimension, char playerCharacther) {
  i8_t win = 1;

  for (i8_t i = 0; i < dimension; ++i) {
    if (board.matrix[i][dimension - 1 - i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

void run_game(board_t board, i8_t turns, i8_t* coordinates) {

  char current_player = '-';
  i8_t free_position = is_empty(board, *coordinates, *(coordinates + 1));
  
  for(i8_t i = 0; i < turns; ++i) {
    
    if(turns % 2 == 0) {
      current_player = 'O';
    }
    else {
      current_player = 'X';
    }

    if(current_player == 'X') {
      if(*coordinates == -1 && state.mouse.left) {
        //Selecione uma posição dentro do tabuleiro
      }
      else if(*coordinates != -1 && state.mouse.left) {
        if(free_position) {
          board.matrix[*coordinates][*(coordinates + 1)] = 'X';
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
        }
        else {
          //Escolha uma casa livre
        }
      }
    }
  }
}
