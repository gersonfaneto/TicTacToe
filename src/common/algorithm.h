#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "common/types.h"

/*** 
* This function dynamically allocates a matrix of characters (char) with 
* the number of rows specified in 'rows' and the number of columns specified in 'cols'.
* @param rows The number of rows in the matrix.
* @param cols The number of columns in the matrix.
* @return A pointer to the allocated matrix.
*/
char **init_Matrix(i8_t rows, i8_t columns);

/*** 
* This function checks if the cell at the specified row and column in the matrix is empty.
* @param row The row index of the cell.
* @param column The column index of the cell.
* @param matrix The matrix to be checked.
* @return 1 if the cell is empty, otherwise 0.
*/
int isEmpty(i8_t row, i8_t column, char **matrix);

/*** 
* This function checks if the player represented by the character 'playerCharacther' has won in any row of the matrix.
* @param dimension The dimension of the matrix (number of rows/columns).
* @param matrix The matrix to be checked.
* @param playerCharacther The character representing the player.
* @return 1 if the player has won, otherwise 0.
*/
int verifyRows(i8_t dimension, char **matrix, char playerCharacther);

/*** 
* This function checks if the player has won in any column of the matrix.
* @param dimension The dimension of the matrix (number of rows/columns).
* @param matrix The matrix to be checked.
* @param playerCharacther The character representing the player.
* @return 1 if the player has won, otherwise 0.
*/
int verifyColumns(i8_t dimension, char **matrix, char playerCharacther);

/**
 * Verifies if the player has won in the main diagonal of the matrix.
 * @param dimension The dimension of the matrix.
 * @param matrix The matrix to be checked.
 * @param playerCharacther The character representing the player.
 * @return Returns 1 if the player has won in the main diagonal, otherwise returns 0.
 */
int verifyMainDiagonal(i8_t dimension, char **matrix, char playerCharacther);

/**
 * Verifies if the player has won in the secondary diagonal of the matrix.
 * @param dimension The dimension of the matrix.
 * @param matrix The matrix to be checked.
 * @param playerCharacther The character representing the player.
 * @return Returns 1 if the player has won in the secondary diagonal, otherwise returns 0.
 */
int verifySecundaryDiagonal(i8_t dimension, char **matrix, char playerCharacther);

/**
 * Prints the matrix in the terminal.
 * @param dimension The dimension of the matrix.
 * @param matrix The matrix to be printed.
 */
void showMatrix(i8_t dimension, char **matrix);

#endif  // !ALGORITHM_H_
