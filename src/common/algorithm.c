#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

char **init_Matrix(i8_t rows, i8_t cols) {
  char **matrix = (char **)malloc(rows * sizeof(char *));

  if (matrix == NULL) {
    printf("Erro: Falha ao alocar memória\n");
    exit(EXIT_FAILURE);
  }

  for (i8_t i = 0; i < rows; ++i) {
    matrix[i] = (char *)malloc(cols * sizeof(char));
    if (matrix[i] == NULL) {
      printf("Erro: Falha ao alocar memória\n");
      exit(EXIT_FAILURE);
    }
    for (i8_t j = 0; j < cols; ++j) {
      matrix[i][j] = '-';
    }
  }

  return matrix;
}

int isEmpty(i8_t row, i8_t column, char **matrix) {
  if (matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

int verifyRows(i8_t dimension, char **matrix, char playerCharacther) {
  int win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    for (i8_t j = 0; j < dimension; ++j) {
      if (matrix[i][j] != playerCharacther) {
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

int verifyColumns(i8_t dimension, char **matrix, char playerCharacther) {
  int win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    for (i8_t j = 0; j < dimension; ++j) {
      if (matrix[j][i] != playerCharacther) {
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

int verifyMainDiagonal(i8_t dimension, char **matrix, char playerCharacther) {
  int win;

  for (i8_t i = 0; i < dimension; ++i) {
    win = 1;
    if (matrix[i][i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

int verifySecundaryDiagonal(i8_t dimension, char **matrix, char playerCharacther) {
  int win = 1;

  for (i8_t i = 0; i < dimension; ++i) {
    if (matrix[i][dimension - 1 - i] != playerCharacther) {
      win = 0;
      break;
    }
  }
  if (win) {
    return 1;
  }
  return 0;
}

void showMatrix(i8_t dimension, char **matrix) {
  for (i8_t i = 0; i<dimension; i++) {
    for (i8_t j; j<dimension; j++) {
      printf("%c \n", matrix[i][j]);
    }
  }
}
