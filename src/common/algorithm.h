#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "common/types.h"
#include "utils/ui.h"
#include "app/appearance.h"

/**
 * Initializes the game by setting up the initial board state.
 *
 * @param board A pointer to the structure representing the game board.
 */
void init_game(board_t *board);

/**
 * Closes the game by performing necessary cleanup operations.
 */
void close_game(void);

/**
 * Checks if a specific position on the board is empty.
 *
 * @param board The structure representing the game board.
 * @param row The row of the position to be checked.
 * @param column The column of the position to be checked.
 * @return 1 if the position is empty, 0 otherwise.
 */
i8_t is_empty(board_t board, i8_t row, i8_t column);

/**
 * Checks if the board is full.
 *
 * @param board The structure representing the game board.
 * @param dimension The size of the board's dimension.
 * @return 1 if the board is full, 0 otherwise.
 */
i8_t is_board_full(board_t board, i8_t dimension);

/**
 * Checks if a player has won.
 *
 * @param board The structure representing the game board.
 * @param dimension The size of the board's dimension.
 * @param playerCharacter The player's character ('X' or 'O').
 * @return 1 if the player has won, 0 otherwise.
 */
i8_t check_win(board_t board, i8_t dimension, char playerCharacter);

/**
 * Checks if the game has ended in a tie.
 *
 * @param board The structure representing the game board.
 * @param dimension The size of the board's dimension.
 * @return 1 if the game has ended in a tie, 0 otherwise.
 */
i8_t check_tie(board_t board, i8_t dimension);

/**
 * Changes the state of the game.
 *
 * @param state The current state of the game.
 * @param button The button pressed by the player.
 */
void change_state(i8_t *state, i8_t *button);

#endif  // !ALGORITHM_H_
