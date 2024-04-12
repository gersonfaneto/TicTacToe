#ifndef WINDOW_H_
#define WINDOW_H_

#include "common/types.h"

typedef struct window_t window_t;

struct window_t {
  i32_t rows;
  i32_t cols;
  i32_t x_pixels;
  i32_t y_pixels;

  void (*read)(window_t* window);
};

window_t init_window(void);

#endif  // !WINDOW_H_
