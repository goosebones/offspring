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


/*
* get the amount of tokens in a string
*
* @param string  string to parse
* @param del  delimiter to count on
* @return number of tokens in string separated my del
*/
int tokenCount(char * string, char del) {
	int count = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == del) {
			count++;
		}
	}
	count++;
	return count;
}

/*
* convert a string into a token array
* tokens are separated by delimiter(s)
*
* @param string  string to tokenize
* @param del  delimiter to separate on
* @param number of tokens in the string
* @return array of strings cooresponding to tokens
*/
char ** tokenArray(char * string, char * del, int elements) {
	char ** tokens = malloc(elements * sizeof(char *));
	int tokensIdx = 0;
	// case where string is one big token or empty string
	if ((elements == 1) && (strcmp(string, "") == 0)) {
		char * emptyString = malloc(strlen(string) * sizeof(char *) + 1);
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
		char * final = malloc(strlen(trimmed) * sizeof(char *) + 1);
		strcpy(final, trimmed);
		tokens[tokensIdx] = final;
		tokensIdx++;
		token = strtok(NULL, del);
	}
	return tokens;
}

/*
* free a token array that is alloced in memory
*
* @param tokens  array of strings
* @param tokenCount  size of token array
*/
void freeTokenArray(char ** tokens, int tokenCount) {
	for (int i = 0; i < tokenCount; i++) {
		free(tokens[i]);
	}
	free(tokens);
}
