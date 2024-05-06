#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include "common/types.h"
#include "utils/ui.h"

typedef struct quadrant_t quadrant_t;

struct quadrant_t{
    i8_t width; 
    i8_t height;
};

quadrant_t init_quadrant();

typedef struct board_t board_t;

struct board_t{
    char matrix[DIMENSION][DIMENSION];

    i8_t row0, row1, row2, row3;
    i8_t col0, col1, col2, col3;
};

board_t init_board();

/**
 * Prints the matrix in the terminal.
 * @param dimension The dimension of the matrix.
 * @param board The matrix to be printed.
 */
void show_board(i8_t dimension, board_t board);

#endif  // !APPEARANCE_H_