#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include "common/types.h"
#include "utils/ui.h"
#include "state.h"

typedef struct quadrant_t quadrant_t;

struct quadrant_t{
    i8_t width; 
    i8_t height;
};

quadrant_t init_quadrant();

typedef struct board_t board_t;

struct board_t{
    i8_t row0;
    i8_t row1;
    i8_t row2;
    i8_t row3;

    i8_t col0;
    i8_t col1;
    i8_t col2;
    i8_t col3;
};

board_t init_board();

#endif  // !APPEARANCE_H_