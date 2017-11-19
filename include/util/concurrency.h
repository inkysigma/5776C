#ifndef CONCURRENCY_MACRO_CONTROL
#define CONCURRENCY_MACRO_CONTROL
#define TASK_PRIORITY_HIGH 4

#define executeUntil(method, condition, timeout) {\
	int time_macro_keeper = 0; \
	while (condition && time_macro_keeper < timeout) { \
		method \
    	delay(40); \
		time_macro_keeper += 40; \
	} \
}

#endif
