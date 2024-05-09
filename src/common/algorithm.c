#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>
#include "state.h"

i8_t is_empty(board_t board, i8_t row, i8_t column) {
  if (board.matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

i8_t is_board_full(board_t board, i8_t dimension) {
  for(i8_t i = 0; i < dimension; ++i) {
    for(i8_t j = 0; j < dimension; ++j) {
      if(board.matrix[i][j] == '-') {
        return 0;
      }
    }
  }
  return 1;
}

i8_t check_win(board_t board, i8_t dimension, char playerCharacter) {
  i8_t main_diag_win = 1;
  i8_t sec_diag_win = 1;

  // Verificar linhas, colunas e diagonais simultaneamente
  for (i8_t i = 0; i < dimension; ++i) {
    i8_t row_win = 1;
    i8_t col_win = 1;

    // Verificar linhas e colunas
    for (i8_t j = 0; j < dimension; ++j) {
      if (board.matrix[i][j] != playerCharacter) {
          row_win = 0;
      }
      if (board.matrix[j][i] != playerCharacter) {
          col_win = 0;
      }
    }

    // Se alguma linha ou coluna ganhou, retorna 1
    if (row_win || col_win) {
      return 1;
    }

    // Verificar a diagonal principal
    if (board.matrix[i][i] != playerCharacter) {
      main_diag_win = 0;
    }

    // Verificar a diagonal secundária
    if (board.matrix[i][dimension - 1 - i] != playerCharacter) {
      sec_diag_win = 0;
    }
  }

  // Se alguma das diagonais ganhou, retorna 1
  if (main_diag_win || sec_diag_win) {
      return 1;
  }

  return 0; // Nenhum ganhador encontrado
}

i8_t check_tie(board_t board, i8_t dimension) {

  if(is_board_full(board, dimension) && !check_win(board, dimension, 'X') && !check_win(board, dimension, 'O')) {
    return 1;
  }
  return 0;
}

