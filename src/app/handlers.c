#define _POSIX_C_SOURCE 199909L

#include "app/handlers.h"

#include <signal.h>

#include "state.h"

void set_handlers(void) {
  struct sigaction sigint = {
      .sa_flags = 0,
      .sa_handler = handle_interruption,
  };

  sigemptyset(&sigint.sa_mask);

  sigaction(SIGINT, &sigint, 0);

  struct sigaction sigwinch = {
      .sa_flags = 0,
      .sa_handler = handle_resizing,
  };

  sigemptyset(&sigint.sa_mask);

  sigaction(SIGWINCH, &sigwinch, 0);
}

void handle_resizing(i32_t signal) {
  state.window.read(&state.window);
}

void handle_interruption(i32_t signal) {
  state.is_running = 0;
}
