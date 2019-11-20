/*
* family tree program
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define MAX_LINE 1024

void interpLine(char * line) {
	for (int i = 0; line[i] != '\0' && line[i] != '\n'; i++) {
		//TODO partition inbetween ','
	}
}

void parseFile(char * filename) {
	errno = 0;
	FILE * file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "error: could not open file '%s'.\n", filename);
		return;
	}

	char line[MAX_LINE];
	while (fgets(line, sizeof(line), file)) {
		interpLine(line);
	}
}

void printPrompt() {
	printf("offspring> ");
}

void entryLoop() {
	char buff[MAX_LINE + 1];\
	char * line;
	printPrompt();
	while ((line = fgets(buff, MAX_LINE, stdin)) != NULL) {
		/*
		// test if input is too long
		int length = strlen(line);
		if (line[length - 1] != '\n') {
			fprintf(stderr, "Input line too long\n");

			char buff2[10000];
			fgets(buff2, 9999, stdin);
			printPrompt();
			continue;
		}
		*/

		/*
		// line cannot be empty
		if (line[0] != '\0') {
			//token(line);
		}
		*/
	}
}

int main(int argc, char * argv[]) {
	if (argc > 1) {
		if (argc > 2) {
			//printUsage();
			return(EXIT_FAILURE);
		} else {
			char * filename = argv[1];
			parseFile(filename);
			// TODO do something with file
		}
	}

	entryLoop();

	return EXIT_SUCCESS;
}
