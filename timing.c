#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>

struct timeval start, end;

int startClock() {
	
	gettimeofday(&start, NULL);
	return 0;
}
int endClock() {
	gettimeofday(&end, NULL);
	fprintf(stderr, "Time Elapsed: %lfs\n", (double)end.tv_sec + (double)end.tv_usec/1000000.0 - (double)start.tv_sec - (double)start.tv_usec/1000000.0);
	return 0;
}