#include "common/algorithm.h"

#include <stdio.h>
#include <stdlib.h>

/*Esta função aloca dinamicamente uma matriz de caracteres (char) com o 
  número de linhas especificado em rows e o número de colunas especificado em cols.*/

char **initializeMatrix(int rows, int cols) {
  char **matrix = (char **)malloc(rows * sizeof(char *));

  if (matrix == NULL) {
    printf("Erro: Falha ao alocar memória\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < rows; ++i) {
    matrix[i] = (char *)malloc(cols * sizeof(char));
    if (matrix[i] == NULL) {
      printf("Erro: Falha ao alocar memória\n");
      exit(EXIT_FAILURE);
    }
    for (int j = 0; j < cols; ++j) {
      matrix[i][j] = '-';
    }
  }

  return matrix;
}

/**/
int isEmpty(int row, int column, char **matrix) {
  if (matrix[row][column] == '-') {
    return 1;
  }
  return 0;
}

/*Esta função verifica se o jogador representado pelo caractere playerCharacther ganhou em alguma linha da matriz.*/
int verifyRows(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
    win = 1;
    for (int j = 0; j < dimension; ++j) {
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

/*Esta função verifica se o jogador ganhou em alguma coluna da matriz.*/
int verifyColumns(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
    win = 1;
    for (int j = 0; j < dimension; ++j) {
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

/*Esta função verifica se o jogador ganhou na diagonal principal da matriz.*/
int verifyMainDiagonal(int dimension, char **matrix, char playerCharacther) {
  int win;

  for (int i = 0; i < dimension; ++i) {
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

/*Esta função verifica se o jogador ganhou na diagonal secundária da matriz.*/
int verifySecundaryDiagonal(int dimension, char **matrix, char playerCharacther) {
  int win = 1;

  for (int i = 0; i < dimension; ++i) {
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
