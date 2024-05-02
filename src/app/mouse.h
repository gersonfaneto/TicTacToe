#ifndef MOUSE_H_
#define MOUSE_H_

//#include "common/types.h"
#include "appearance.h"

/**
 * struct mouse_t - Defines a model to store the information related to the
 * mouse, like its current states and position.
 */
typedef struct mouse_t mouse_t;

struct mouse_t {
  i32_t fd;
  i32_t x;
  i32_t y;
  i8_t left;
  i8_t middle;
  i8_t right;

  /**
   * @brief Reads and decodes the information available on the `MOUSE_DEVICE_PATH`,
   * assigning the decoded values to the proper fields of the `struct mouse_t`.
   *
   * @param[inout] mouse The `struct mouse_t` to be updated.
   * @param[in] rows The number of rows in the current window.
   * @param[in] cols The number of cols in the current window.
   */
  void (*read)(mouse_t* mouse, i32_t rows, i32_t cols);
};

/**
 * @brief Initialize the `struct mouse_t` by assigning its defaults. May fail
 * if the `MOUSE_DEVICE_PATH` macro isn't defined or if the associated file
 * can't be opened.
 *
 * @return The properly initialized `struct mouse_t`.
 */
mouse_t init_mouse(void);

i8_t* get_mouse(i8_t mouse_x, i8_t mouse_y, board_t board);

#endif  // !MOUSE_H_
