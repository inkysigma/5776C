#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL

#define executeUntil(method, condition, timeout) {\
	long time_macro_keeper = 0;
	while (condition && time_macro_keeper < timeout) { \
		method \
    		delay(20);
		time_macro_keeper += 20;
	} \
}

#endif
