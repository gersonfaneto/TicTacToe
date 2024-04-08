#ifndef ASSERT_H_
#define ASSERT_H_

#define __assert(condition, format, ...)                                       \
  if (!(condition)) {                                                          \
    fprintf(stderr, format "\n", ##__VA_ARGS__);                               \
    exit(1);                                                                   \
  }

#endif  // !ASSERT_H_
