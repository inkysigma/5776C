void defensive() {
#if BLUE
	moveDrive(127, 127);
#else
	moveDrive(127, 127);
#endif
	delay(4000);
	moveDrive(-10, -10);
	delay(100);
	moveDrive(0, 0);
}
