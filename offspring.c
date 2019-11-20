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
	/*
	int commandIdx = 0;
	for (int i = 0; i < MAX_COMMAND && line[i] != '\0'; i++) {
		char c = line[i];
		if (c == ' ') {
			commandIdx = i;
			break;
		} else {
			commandIdx = i;
		}
	}
	return commandIdx;
	*/
	char command[MAX_COMMAND + 1];
	int i;
	for (i = 0; i < MAX_COMMAND && line[i] != '\0'; i++) {
		if (line[i] == ' ') {
			break;
		}
		command[i] = line[i];
	}
	command[i] = '\0';

	char * allocCommand = malloc(strlen(command) * sizeof(char));
	strcpy(allocCommand, command);
	printf("command: %s\n", allocCommand);
	return allocCommand;
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
		/*
		// get index that command ends at
		int commandIdx = getCommandIdx(trimmed);

		// make command string
		char command[commandIdx + 2];
		strncpy(command, trimmed, commandIdx + 1);
		command[commandIdx + 2] = '\0';
		*/


		char * command = getCommand(trimmed);
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
