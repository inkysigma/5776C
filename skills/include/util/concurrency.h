#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL
#define TASK_PRIORITY_HIGH 4

/**
 *	Execute a task until a condition is met or a timeout is reached. The
 * method is a macro and a shortcut for simply waiting and looping. Please be
 * aware of a small incursion in memory space that will result from usage of
 * this method.
 **/
#define executeUntil(method, condition, timeout)                               \
  {                                                                            \
    int time_macro_keeper = 0;                                                 \
    while ((condition) && time_macro_keeper < timeout) {                       \
      {method} delay(20);                                                      \
      time_macro_keeper += 20;                                                 \
    }                                                                          \
  \
}

/**
 * Wait until a condition is met or a timeout is reached. The method is a macro
 * and a shortcut for simply waiting and looping. Please be aware of a small
 * incursion in memory space that will result from usage of this method.
 **/
#define waitUntil(condition, timeout)                                          \
  {                                                                            \
    int time_macro_keeper = 0;                                                 \
    while ((condition) && time_macro_keeper < timeout) {                       \
      delay(20);                                                               \
      time_macro_keeper += 20;                                                 \
    }                                                                          \
  \
}

#endif
