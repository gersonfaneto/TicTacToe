#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "common/types.h"

/**
 * @brief Sets the handlers for events related to the current window.
 */
void set_handlers(void);

/**
 * @brief Handles the signal emitted when the window is resided, by updating
 * the values stored in the `struct window_t` stored under the `struct state_t`.
 *
 * @param[in] signal The signal emitted by the event.
 */
void handle_resizing(i32_t signal);

/**
 * @brief Handles the signal emitted when the user attempts to brutally interrupt
 * the execution of the process, by pressing `<C-c>`, by setting the `is_running`
 * flag under the `struct state_t` to 0. 
 *
 * @param[[TODO:direction]] signal [TODO:description]
 */
void handle_interruption(i32_t signal);

#endif  // !HANDLERS_H_
