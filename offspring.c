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
#include <stdbool.h>

#include "trimit.h"
#include "tree_node.h"
#include "arg_parse.h"

#define MAX_LINE 1024
#define MAX_COMMAND 6

static tree_node_t * tree = NULL;

void interpLine(char * line) {
	//TODO check for single name on first line
	int argCount = tokenCount(line, ',');
	char ** tokens  = tokenArray(line, ",", argCount);
	for (int i = 1; i < argCount; i++) {
		tree = add_child(tree, tokens[0], tokens[i]);
	}
	freeTokenArray(tokens, argCount);
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
	fclose(file);
}

void printPrompt() {
	printf("offspring> ");
}

void printHelp() {
	printf( "User Commands for offspring:\n"
		"add parent-name, child-name # find parent and add child.\n"
		"find name	# search and print name and children if name is found.\n"
		"print [name]	# breadth first traversal of offspring from name.\n"
		"size [name]	# count members in the [sub]tree.\n"
		"height [name]	# return the height of [sub]tree.\n"
		"init		# delete current tree and restart with an empty tree.\n"
		"help		# print this information.\n"
		"quit		# delete current tree and end program.\n"
		);
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

	char * allocCommand = malloc(strlen(command) * sizeof(char) + 1);
	strcpy(allocCommand, command);
	return allocCommand;
}

bool commandIs(char * commandName, char * commandInput) {
	if (strcmp(commandName, commandInput) == 0) {
		return true;
	} else {
		return false;
	}
}

void doCommand(char * command, char * args) {
	int argCount = tokenCount(args, ',');
	char ** tokens = tokenArray(args, ",", argCount);
	if (commandIs("add", command)) {
		for (int i = 1; i < argCount; i++) {
			tree = add_child(tree, tokens[0], tokens[i]);
		}
	} else if (commandIs("find", command)) {
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		if (treeNode == NULL) {
			fprintf(stderr, "Error: '%s' not found.\n", tokens[0]);
		} else {
			print_offspring_line(treeNode);
		}
	} else if (commandIs("print", command)) {
		print_tree(tree, tokens[0]);
	} else if (commandIs("size", command)) {
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		int size;
		if (argCount == 0) {
			size = get_tree_size(tree);
		} else if (treeNode == NULL) {
			size = 0;
		} else {
			size = get_tree_size(treeNode);
		}
		printf("size: %d\n", size);
	} else if (commandIs("height", command)) {
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		int height;
		if (argCount == 0) {
			height = get_tree_height(tree);
		} else if (treeNode == NULL) {
			height = -1;
		} else {
			height = get_tree_height(treeNode);
		}
		printf("height: %d\n", height);
	} else if (commandIs("help", command)) {
		printHelp();
	} else if (commandIs("init", command)) {
		destroy_tree(tree);
		tree = NULL;
	} else if (commandIs("quit", command)) {
		destroy_tree(tree);
		freeTokenArray(tokens, argCount);
		free(command);
		exit(EXIT_SUCCESS);
	} else {
		fprintf(stderr, "Unknown Command: %s\n", command);
	}
	freeTokenArray(tokens, argCount);
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

		printf("+ %s\n\n", trimmed);
		// gets command in a molloced string
		// trimmed is modefied to get more spaces
		char * command = getCommand(trimmed);
		// put args into malloced string and free line
		char * commandArgs = trim(line);

		doCommand(command, commandArgs);

		free(command);

		printPrompt();
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
		}
	}

	entryLoop();

	return EXIT_SUCCESS;
}
