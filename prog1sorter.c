#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "readArgs.h"

void getuser(void);

int main(int argc, char **argv) {
	int i;
	char *userid = getenv("USER");
	
	int numbers = 100;
	int min = 1;
	int max = 255;
	FILE *infile = NULL;
	FILE *outfile = NULL;
	FILE *userfile = NULL;
	
	/* Send off arguments to be read */
	int q = readArgs(argc, argv, &numbers, &min, &max, 0, &infile, outfile, userfile);
	
	/* Check if -u usage is asked for */
	if(q==1) {
		fprintf(stderr,"This is an integer sorting program!\n");
		exit(0);
	}
	if(infile != NULL) {
		char buff[255];
		fscanf(infile, "%s", buff);
		printf("%s\n",buff);
	}
	if(infile != NULL) {
		fclose(infile);
	}
	
	
	return 0;
}

void getuser(void) {
	char *userid = getenv("USER");
	printf("User: %s\n",userid);
}