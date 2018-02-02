#ifndef READ_ARGS
#define READ_ARGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int readArgs(int a, char **argv, int*, int*, int*, int*, FILE**, FILE*, FILE*);

void argerror(void);
int readArgs(int argc, char **argv, int* numbers, int* min, int*max, int*seed, FILE** infile, FILE* outfile, FILE* userfile) {
	
	int i;
	
	for(i=0;i<argc;i++) {
		if(strstr(argv[i],"-u") != NULL) {
			return(1);
		}
	}
	for(i=1;i<argc;i=++i) {
		if (strcmp(argv[i], "-n") == 0) { /* NUMBER OF INTEGERS */
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
			int newNum = atoi(argv[i]);
			*numbers = newNum;
		} else if (strcmp(argv[i], "-m") == 0) { /* MINIMUM */
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
			int newMin = atoi(argv[i]);
			*min = newMin;
		} else if (strcmp(argv[i], "-M") == 0) { /* MAXIMUM */
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
			int newMax = atoi(argv[i]);
			*max = newMax;
		} else if (strcmp(argv[i], "-s") == 0) { /* SEED */
			if(strcmp(argv[0], "./prog1sorter") == 0) {
				argerror();
				return(1);
			}
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
		} else if (strcmp(argv[i], "-i") == 0) { /* INPUT FILE */
			if(strcmp(argv[0], "./prog1generator") == 0) {
				argerror();
				return(1);
			}
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
			*infile = fopen(argv[i],"r");
		} else if (strcmp(argv[i], "-o") == 0) { /* OUTPUT FILE */
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
		} else if (strcmp(argv[i], "-c") == 0) { /* C FILE */
			if(strcmp(argv[0], "./prog1generator") == 0) {
				argerror();
				return(1);
			}
			++i;
			if(i==argc) {
				argerror();
				return(1);
			}
			
		} else {
			return(1);
		}
	}

	
	return(0);
}

void argerror() {
	fprintf(stderr, "Invalid or incomplete option. Printing usage:\n");
}

#endif