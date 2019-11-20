/*
* family tree program
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "trimit.h"

#define MAX_LINE 1024
#define MAX_COMMAND 6

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

char * getCommand(char * line){
	char command[MAX_COMMAND + 1];
	int i;
	for (i = 0; i < MAX_COMMAND && line[i] != '\0'; i++) {
		if (line[i] == ' ') {
			break;
		}
		command[i] = line[i];
		line[i] = ' ';
	}
	command[i] = '\0';

	char * allocCommand = malloc(strlen(command) * sizeof(char));
	strcpy(allocCommand, command);
	printf("line: %s\n", line);
	printf("command: %s\n", allocCommand);
	return allocCommand;
}

void doCommand(char * command, char * args) {
	if (strcmp(command, "add")) {
		// add
	} else if (strcmp(command, "find")) {
		// find
	} else if (strcmp(command, "print")) {
		// print
	} else if (strcmp(command, "size")) {
		// size
	} else if (strcmp(command, "height")) {
		// height
	} else if (strcmp(command, "help")) {
		// help
	} else if (strcmp(command, "init")) {
		// init
	} else if (strcmp(command, "quit")) {
		// quit
	} else {
		// unknown
	}
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



		// trim start and end whitespace
		char * trimmed = trim(line);
		// gets command in a molloced string
		// trimmed is modefied to get more spaces
		char * command = getCommand(trimmed);
		// put args into malloced string and free line
		char * commandArgs = trim(line);
		free(line);

		doCommand(command, commandArgs);
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
