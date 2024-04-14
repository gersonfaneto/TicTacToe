#ifndef STATE_H_
#define STATE_H_

#include "app/mouse.h"
#include "app/window.h"

typedef struct state_t state_t;

struct state_t {
  window_t window;
  mouse_t mouse;

  volatile i32_t is_running;
};

extern state_t state;

#endif  // !STATE_H_
