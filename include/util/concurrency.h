#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL

#define executeUntil(method, condition, timeout) {\
	while (condition && time1[T1] < timeout) { \
		method \
    delay(timeout)
	} \
}

#endif
