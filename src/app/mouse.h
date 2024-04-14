#ifndef MOUSE_H_
#define MOUSE_H_

#include "common/types.h"

typedef struct mouse_t mouse_t;

struct mouse_t {
  i32_t fd;
  i32_t x;
  i32_t y;
  i8_t left;
  i8_t middle;
  i8_t right;

  void (*read)(mouse_t* mouse, i32_t rows, i32_t cols);
};

mouse_t init_mouse();

#endif  // !MOUSE_H_
