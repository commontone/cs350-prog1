#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "readArgs.h"
#include "timing.h"


int main(int argc, char **argv) {
	
	/* Initialize values */
	int i = 0;
	int temp = 0;
	int numbers = 1000000000;
	numbers = 100;
	unsigned long seed = 0;
	int min = 1;
	int max = 255;
	FILE *outfile = NULL;
	
	/* Send off arguments to be read */
	int q = readArgs(argc, argv, &numbers, &min, &max, &seed, 0, &outfile, 0);
	
	/* Check if -u usage is asked for */
	if(q==1) {
		fprintf(stderr,"This is an integer generating program!\n [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]");
		exit(0);
	}
	
	/* Check num integers bounds */
	if(numbers<0 || numbers>1000000) {
		fprintf(stderr, "The number of integers must be within [0 - 1,000,000].\n");
		exit(0);
	}
	
	/* Check max/min validity */
	if(max > 1000000) {
		fprintf(stderr, "The integer maximum cannot be larger than 1,000,000.\n");
		exit(0);
	}
	if(min < 1) {
		fprintf(stderr, "The integer minimum cannot be less than 1.\n");
		exit(0);
	}
	if(min > max) {
		fprintf(stderr, "The integer minimum cannot be larger than the integer maximum.\n");
		exit(0);
	}
	
	/* Begin Timing */
	startClock();
	
	/* Create Integer Array */
	int* ints;
	ints = (int*)calloc(numbers,(sizeof(int)));
	
	if(seed!=0) {
		srand (seed);
	} else {
		srand (time(NULL));
	}
	
	for(i=0;i<numbers;++i) {
		ints[i]=0;
		int ins = rand()%(max-min)+min;
		ints[i] = ins;
	}
	
	/* Print Integers to File or STDOUT */
	if(outfile != NULL) {
		fprintf(outfile, "%d\n", numbers);
		for(i=0;i<numbers;++i) {
			fprintf(outfile, "%d\n", ints[i]);
		}
	} else {
		fprintf(stdout, "%d\n", numbers);
		for(i=0;i<numbers;++i) {
			fprintf(stdout, "%d\n", ints[i]);
		}
	}
	
	/* Stop Timing */
	endClock();
	
	/* Close Files */
	if(outfile != NULL) {
		fclose(outfile);
	}
	free(ints);
	
	return 0;
}

