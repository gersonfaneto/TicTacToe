#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

void init_matrix(board_t board, i8_t dimension) {
  for(i8_t i = 0; i < dimension; ++i) {
    for(i8_t j = 0; j < dimension; ++j) {
      board.matrix[i][j] = '-';
    }
  }
}

int isEmpty(board_t board, i8_t row, i8_t column) {
  if (board.matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

int verifyRows(board_t board, i8_t dimension, char playerCharacther) {
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

int verifyColumns(board_t board, i8_t dimension, char playerCharacther) {
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

int verifyMainDiagonal(board_t board, i8_t dimension, char playerCharacther) {
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

int verifySecundaryDiagonal(board_t board, i8_t dimension, char playerCharacther) {
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

