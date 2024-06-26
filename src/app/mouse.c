#include "app/mouse.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "config.h"
#include "appearance.h"
#include "state.h"

void read_mouse(mouse_t* mouse, i32_t rows, i32_t cols) {
  i8_t data[3] = {0};

  i8_t result = read(mouse->fd, data, sizeof(data));

  if (result > 0) {
    mouse->left = (data[0] & 0x1) ? 1 : 0;
    mouse->right = (data[0] & 0x2) ? 1 : 0;
    mouse->middle = (data[0] & 0x4) ? 1 : 0;

    mouse->x += (data[1] / ((MOUSE_SENSIBILITY > 0) ? MOUSE_SENSIBILITY : 1));

    if (mouse->x < 0) {
      mouse->x = 0;
    }

    if (mouse->x > cols) {
      mouse->x = cols;
    }

    mouse->y += ((data[2] * -1) / ((MOUSE_SENSIBILITY > 0) ? MOUSE_SENSIBILITY : 1));

    if (mouse->y < 0) {
      mouse->y = 0;
    }

    if (mouse->y > rows) {
      mouse->y = rows;
    }
  }
}

mouse_t init_mouse(void) {
  i32_t fd = open(MOUSE_DEVICE_PATH, O_RDONLY);

  if (fd == -1) {
    fprintf(stderr, "Failed to open file \"%s\" :: Cause %s.\n", MOUSE_DEVICE_PATH, strerror(errno));
    exit(1);
  }

  return (mouse_t){
      .fd = fd,
      .x = state.window.cols * 0.5,
      .y = state.window.rows * 0.5,
      .left = 0,
      .right = 0,
      .middle = 0,
      .read = read_mouse,
  };
}

i8_t* get_mouse(i8_t mouse_x, i8_t mouse_y, board_t board) {

    i8_t* array = malloc(2 * sizeof(int8_t));

    if (array == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    if(mouse_x >= board.col0 && mouse_x <= board.col3 && mouse_y >= board.row0 && mouse_y <= board.row3) {

        if(mouse_x > board.col0 && mouse_x < board.col1 && mouse_y > board.row0 && mouse_y < board.row1) {
            array[0] = 0;
            array[1] = 0;
        }
        else if(mouse_x > board.col1 && mouse_x < board.col2 && mouse_y > board.row0 && mouse_y < board.row1) {
            array[0] = 0;
            array[1] = 1;
        }
        else if(mouse_x > board.col2 && mouse_x < board.col3 && mouse_y > board.row0 && mouse_y < board.row1) {
            array[0] = 0;
            array[1] = 2;
        }
        else if(mouse_x > board.col0 && mouse_x < board.col1 && mouse_y > board.row1 && mouse_y < board.row2) {
            array[0] = 1;
            array[1] = 0;
        }
        else if(mouse_x > board.col1 && mouse_x < board.col2 && mouse_y > board.row1 && mouse_y < board.row2) {
            array[0] = 1;
            array[1] = 1;
        }
        else if(mouse_x > board.col2 && mouse_x < board.col3 && mouse_y > board.row1 && mouse_y < board.row2) {
            array[0] = 1;
            array[1] = 2;
        }
        else if(mouse_x > board.col0 && mouse_x < board.col1 && mouse_y > board.row2 && mouse_y < board.row3) {
            array[0] = 2;
            array[1] = 0;
        }
        else if(mouse_x > board.col1 && mouse_x < board.col2 && mouse_y > board.row2 && mouse_y < board.row3) {
            array[0] = 2;
            array[1] = 1;
        }
        else if(mouse_x > board.col2 && mouse_x < board.col3 && mouse_y > board.row2 && mouse_y < board.row3) {
            array[0] = 2;
            array[1] = 2;
        }
        else {
          array[0] = -1;
          array[1] = -1;
        }
    }
    else {
        array[0] = -1;
        array[1] = -1;
    }

  return array;
}
