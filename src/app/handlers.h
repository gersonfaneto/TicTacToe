#ifndef HANDLERS_H_
#define HANDLERS_H_

#include "common/types.h"

void set_handlers(void);

void handle_resizing(i32_t signal);
void handle_interruption(i32_t signal);

#endif  // !HANDLERS_H_
