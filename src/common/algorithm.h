#ifndef ALGORITHM_H_
#define ALGORITHM_H_

char **init_Matrix(int rows, int columns);

int isEmpty(int row, int column, char **matrix);

int verifyRows(int dimension, char **matrix, char playerCharacther);

int verifyColumns(int dimension, char **matrix, char playerCharacther);

int verifyMainDiagonal(int dimension, char **matrix, char playerCharacther);

int verifySecundaryDiagonal(int dimension, char **matrix, char playerCharacther);

void showMatrix(int dimension, char **matrix);

#endif  // !ALGORITHM_H_
