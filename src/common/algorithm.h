#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "common/types.h"
#include "utils/ui.h"
#include "app/appearance.h"

i8_t is_empty(board_t board, i8_t row, i8_t column);

i8_t is_board_full(board_t board, i8_t dimension);

i8_t check_win(board_t board, i8_t dimension, char playerCharacter);

i8_t check_tie(board_t board, i8_t dimension);

#endif  // !ALGORITHM_H_
