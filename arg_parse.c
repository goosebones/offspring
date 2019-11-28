/*
* implementation of funtions described in arg_parse.h
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arg_parse.h"
#include "trimit.h"

int tokenCount(char * string, char del) {
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == del) {
			count++;
		}
	}
	//if (count == 0) {
	//	return 0;
	//} else {
	//	count++;
	//	return count;
	//}
	count++;
	return count;
}


char ** tokenArray(char * string, char * del, int elements) {
	// make char * of size elements
	// use strtok to get to split on thing
	// take that string and use trim
	// put trimmed string into char[]
	//if (elements == 0) {
	//	return NULL;
	//}
	char ** tokens = malloc(elements * sizeof(char *));
	int tokensIdx = 0;

	if ((elements == 1) && (strcmp(string, "") == 0)) {
		char * emptyString = malloc(strlen(string) * sizeof(char *));
		strcpy(emptyString, string);
		tokens[0] = emptyString;
		return tokens;
	}

	char stringCopy[strlen(string)];
	strcpy(stringCopy, string);
	char * token = strtok(stringCopy, del);
	while(token != NULL) {
		if (tokensIdx >= elements) {
			fprintf(stderr, "Argument parsing error.");
			exit(EXIT_FAILURE);
		}
		char * trimmed = trim(token);
		char * final = malloc(strlen(trimmed) * sizeof(char *));
		strcpy(final, trimmed);
		tokens[tokensIdx] = final;
		tokensIdx++;
		token = strtok(NULL, del);
	}
	return tokens;
}

void freeTokenArray(char ** tokens, int tokenCount) {
	for (int i = 0; i < tokenCount; i++) {
		free(tokens[i]);
	}
	free(tokens);
}

/*
int main() {
	char * thad = "thadeous, tabo  nia, jones, jenkins, jr 3";
	int i = tokenCount(thad, ',');
	printf("tokenCount: %d\n", i);
	char ** tokens = tokenArray(thad, ",", i);
	printf("tokens[0]: %s\n", tokens[0]);
	printf("tokens[1]: %s\n", tokens[1]);
	printf("tokens[4]: %s\n", tokens[4]);
	freeTokenArray(tokens, i);
	return 0;
}
*/
