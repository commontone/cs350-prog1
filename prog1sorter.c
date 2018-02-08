#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include "readArgs.h"
#include "timing.h"

void userPrint(FILE**, int*, int);
int intcompare(const void*, const void*);

int main(int argc, char **argv) {
	
	/* Initialize values */
	int i = 0;
	int temp = 0;
	int numbers = 1000000;
	numbers = 90;
	int min = 1;
	int max = 255;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	FILE *userfile = NULL;
	
	/* Send off arguments to be read */
	int q = readArgs(argc, argv, &numbers, &min, &max, 0, &infile, &outfile, &userfile);
	
	/* Check if -u usage is asked for */
	if(q==1) {
		fprintf(stderr,"This is an integer sorting program!\n[-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]");
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
	
	/* Check if using an input file and set number of ints accordingly */
	if(infile != NULL) {
		fscanf(infile, "%d", &numbers);
		int* ints;
		ints = (int*)calloc(numbers,(sizeof(int)));
	}
	
	/* Check num integers bounds */
	if(numbers<0 || numbers>1000000) {
		fprintf(stderr, "The number of integers must be within [0 - 1,000,000].\n");
		exit(0);
	}
	
	/* Begin Timing */
	startClock();
	
	/* Create Integer Array */
	
	int* ints;
	if(infile != NULL) {
		ints = (int*)calloc(numbers,(sizeof(int)));
	}
	
	/* Populate Integer Array */
	if(infile != NULL) {
		char buff[255];
		for(i=0;i<numbers;++i) {
			ints[i]=0;
			int res = fscanf(infile, "%s\n", buff);
			if(res==-1) {
				fprintf(stderr, "Reported number of integers is too high. Exiting");
				exit(0);
			}
			temp = atoi(buff);
			if(temp>max || temp<min) {
				fprintf(stderr, "Integer of Max/Min bounds. Exiting.");
				exit(0);
			}
			ints[i] = temp;
			buff[255] = '\0';
			
		}
		int res = fscanf(infile, "%s\n", buff);
		if(res!=-1) {
			fprintf(stderr, "Reported number of integers is too low. Exiting");
			exit(0);
		}
	}
	else {
		fscanf(stdin, "%d\n", &numbers);
		ints = (int*)calloc(numbers,(sizeof(int)));
		for(i=0;i<numbers;++i) {
			ints[i]=0;
			int ins = 0;
			fscanf(stdin, "%d", &ins);
			ints[i] = ins;
		}
	}
	

	
	/* Sort the Integers */
	qsort(ints, numbers, sizeof(int), intcompare);
	
	/* Print Integers to File or STDOUT */
	if(outfile != NULL) {
		for(i=0;i<numbers;++i) {
			fprintf(outfile, "%d\n", ints[i]);
		}
	} else {
		for(i=0;i<numbers;++i) {
			fprintf(stdout, "%d\n", ints[i]);
		}
	}
	
	/* Compute and Send USER-based output */
	userPrint(&userfile, ints, numbers);

	/* Stop Timing */
	endClock();
	
	/* Close All Files */
	if(infile != NULL) {
		fclose(infile);
	}
	if(outfile != NULL) {
		fclose(outfile);
	}
	if(userfile != NULL) {
		fclose(userfile);
	}
	free(ints);
	return 0;
}

void userPrint(FILE** userfile, int* ints, int nums) {
	int i = 0;
	char *userid = getenv("USER");
	int userd = strlen(userid);
	int* counts;
	counts = (int*)malloc((sizeof(int))*userd);
	
	/* Tally Character Counts */
	for(i=0;i<userd;++i) {
		int j = 0;
		counts[i] = 0;
		for(j=0;j<nums;++j) {
			
			if((int)userid[i]==ints[j]) {
				counts[i] = counts[i] + 1;
			}
		}
	}
	
	/* Send Tally to Output */
	if(*userfile != NULL) {
		
		for(i=0;i<strlen(userid);++i) {
			fprintf(stdout, "%c",userid[i]);
		}
		
		for(i=0;i<strlen(userid);++i) {
			fprintf(*userfile, "%c\t%d\t%d\n",userid[i], (int)userid[i], counts[i]);
		}
	} else {
		for(i=0;i<strlen(userid);++i) {
			fprintf(stdout, "%c\t%d\t%d\n",userid[i], (int)userid[i], counts[i]);
		}
	}
	
	free(counts);
}

int intcompare(const void* a, const void* b) {
	/* compare two ints */
	return(*(int*)a - *(int*)b );
}






















