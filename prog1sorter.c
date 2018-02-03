#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "readArgs.h"

void userPrint(FILE**, int**);
int intcompare(const void*, const void*);

int main(int argc, char **argv) {
	
	/* Initialize values */
	int i;
	int numbers = 100;
	int sortnum = 100;
	int min = 1;
	int max = 255;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	FILE *userfile = NULL;
	char *userid = getenv("USER");
	
	/* Send off arguments to be read */
	int q = readArgs(argc, argv, &numbers, &min, &max, 0, &infile, &outfile, &userfile);
	
	/* Check if -u usage is asked for */
	if(q==1) {
		fprintf(stderr,"This is an integer sorting program!\n");
		exit(0);
	}
	
	/* Check num integers bounds */
	if(numbers<0 || numbers>1000000) {
		fprintf(stderr, "The number of integers must be within [0 - 1,000,000]");
		exit(0);
	}
	
	/* Check if using an input file and set number of ints accordingly */
	if(infile != NULL) {
		char buff[255];
		fscanf(infile, "%s", buff);
		numbers = atoi(buff);
	}
	
	/* Create Integer Array */
	int* ints;
	ints = (int*)malloc((sizeof(int))*numbers);
	printf("Ints array size: %d\n",(int)((sizeof(int))*numbers));
	
	/* Populate Integer Array */
	if(infile != NULL) {
		char buff[255];
		for(i=0;i<numbers;++i) {
			ints[i]=0;
			fscanf(infile, "%s", buff);
			ints[i] = atoi(buff);
		}
	}
	else {
		fscanf(stdin, "%d", &numbers);
		char buff[255];
		for(i=0;i<numbers;++i) {
			ints[i]=0;
			int ins;
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
	
	userPrint(&userfile, &ints);
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

void userPrint(FILE** userfile, int** intz) {
	char *userid = getenv("USER");
	if(*userfile != NULL) {
		fprintf(*userfile, "Test!\n");
		printf("User: %s\n",userid);
		
		
	} else {
		fprintf(stdout, "Testing\n");
	}
}

int intcompare(const void* a, const void* b) {
	return(*(int*)a - *(int*)b );
}






















