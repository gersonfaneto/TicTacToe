#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include "common/types.h"
#include "utils/ui.h"

typedef struct quadrant quadrant;

struct quadrant{
    i8_t width; 
    i8_t height;
};

quadrant init_quadrant();

typedef struct board board;

struct board{
    i8_t middle_x;
    i8_t middle_y;
    i8_t width;
    i8_t height;
};

board init_board();

#endif  // !APPEARANCE_H_