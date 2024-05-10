#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include "common/types.h"
#include "utils/ui.h"

// Structure representing a quadrant
typedef struct quadrant_t quadrant_t;

struct quadrant_t {
    i8_t width;  // Width of the quadrant
    i8_t height; // Height of the quadrant
};

/**
 * Initializes a quadrant with default width and height.
 *
 * @return Initialized quadrant.
 */
quadrant_t init_quadrant(void);

// Structure representing the game board
typedef struct board_t board_t;

struct board_t {
    char matrix[DIMENSION][DIMENSION]; // Matrix representing the game board

    // Coordinates of the rows
    i8_t row0, row1, row2, row3;

    // Coordinates of the columns
    i8_t col0, col1, col2, col3;
};

/**
 * Initializes the game board.
 *
 * @return Initialized game board.
 */
board_t init_board(void);

/**
 * Displays the players' characters.
 *
 * @param currentPlayer The character of the current player.
 */
void show_players(char currentPlayer);

/**
 * Displays the contour of the game board.
 *
 * @param dimension The dimension of the game board.
 * @param board The game board.
 */
void show_contour(i8_t dimension, board_t board);

/**
 * Displays the victory message for player X.
 */
void show_victory_X(void);

/**
 * Displays the victory message for player O.
 */
void show_victory_O(void);

/**
 * Displays the tie message.
 */
void show_tie(void);

/**
 * Prints the matrix representing the game board.
 *
 * @param dimension The dimension of the game board.
 * @param board The game board matrix.
 */
void show_board(i8_t dimension, board_t board);

/**
 * Displays the retry message.
 */
void retry_message(void);

/**
 * Displays an error message for selecting a position outside the game board.
 */
void out_of_board_error(void);

/**
 * Displays an error message for selecting an invalid position.
 */
void invalid_position_error(void);

/**
 * Displays the initial message.
 */
void init_message(void);

/**
 * Displays the mouse.
 */
void print_mouse(void);

#endif  // !APPEARANCE_H_
