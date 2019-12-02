/*
* implementation of a family tree
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

// max size of input lines
#define MAX_LINE 1024
// max length of valid command
#define MAX_COMMAND 6

// current family tree
static tree_node_t * tree = NULL;


/*
* insert family members into tree
* used input from user provided file
*
* @param line  parent-child relationship line
*/
void interpLine(char * line) {
	//TODO check for single name on first line
	int argCount = tokenCount(line, ',');
	char ** tokens  = tokenArray(line, ",", argCount);
	for (int i = 1; i < argCount; i++) {
		tree = add_child(tree, tokens[0], tokens[i]);
	}
	freeTokenArray(tokens, argCount);
}

void onePersonTree(char * line) {
	int argCount = tokenCount(line, ',');
	char ** tokens = tokenArray(line, ",", argCount);
	tree = create_node(tokens[0]);
	freeTokenArray(tokens, argCount);
}

/*
* initialize a family tree from a user supplied file
*
* @param filename  file to read family from
*/
void parseFile(char * filename) {
	errno = 0;
	FILE * file = fopen(filename, "r");
	if (!file) {
		fprintf(stderr, "error: could not open file '%s'.\n", filename);
		return;
	}

	char line[MAX_LINE];
	int lineNumber = 1;
	while (fgets(line, sizeof(line), file)) {
		printf("line:%s\n", line);
		if (lineNumber == 1) {
			int argCount = tokenCount(line, ',');
			if (argCount == 1) {
				onePersonTree(line);
			} else {
				interpLine(line);
			}
		} else {
			interpLine(line);
		}
		lineNumber++;
	}
	fclose(file);
}

/*
* print input prompt
* used to signify when the program is ready for input
*/
void printPrompt() {
	printf("offspring> ");
}

/*
* print command line usage message
*/
void printUsage() {
	fprintf(stderr, "Usage: offspring [offspring-file]\n");
}

/*
* print the help message
*/
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

/*
* get the command from a user input line
* command will be first non-whitespace sequence of characters
*
* @param line  user supplied input
* @return allocated command string
*/
char * getCommand(char * line){
	// valid commands' length is capped at MAX_COMMAND
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

/*
* helper function to determine what a user command is
* used strcmp()
*
* @param commandName  predetermined valid command
* @param commandInput   user supplied command
* @return true of commands match, false otherwise
*/
bool commandIs(char * commandName, char * commandInput) {
	if (strcmp(commandName, commandInput) == 0) {
		return true;
	} else {
		return false;
	}
}

/*
* execute a user supplied command
*
* @param command  user supplied command
* @param args  remaining string containing potential command arguments
*/
void doCommand(char * command, char * args) {
	// create token arrar for arguments
	int argCount = tokenCount(args, ',');
	char ** tokens = tokenArray(args, ",", argCount);

	// add
	if (commandIs("add", command)) {
		if (argCount == 1) {
			fprintf(stderr, "Usage: 'add parent name, child name'.\n");
		}
		// each arg is added to the tree
		for (int i = 1; i < argCount; i++) {
			tree = add_child(tree, tokens[0], tokens[i]);
		}
	// find
	} else if (commandIs("find", command)) {
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		// if name is not found in tree
		if (treeNode == NULL) {
			fprintf(stderr, "error: '%s' not found.\n", tokens[0]);
		} else {
			print_offspring_line(treeNode);
		}
	// print
	} else if (commandIs("print", command)) {
		print_tree(tree, tokens[0]);
	// size
	} else if (commandIs("size", command)) {
		// get node of person to start at
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		int size;
		// no argument means size of entire tree
		if (argCount == 0) {
			size = get_tree_size(tree);
		// specified starting name was not found
		} else if (treeNode == NULL) {
			size = 0;
		// valid starting name
		} else {
			size = get_tree_size(treeNode);
		}
		printf("size: %d\n", size);
	// height
	} else if (commandIs("height", command)) {
		// get node of perosn to start at
		tree_node_t * treeNode = find_node(tree, tokens[0]);
		int height;
		// no argument means height of entire tree
		if (argCount == 0) {
			height = get_tree_height(tree);
		// specified starting name was not found
		} else if (treeNode == NULL) {
			height = -1;
		// valid starting name
		} else {
			height = get_tree_height(treeNode);
		}
		printf("height: %d\n", height);
	// help
	} else if (commandIs("help", command)) {
		printHelp();
	// init
	} else if (commandIs("init", command)) {
		// start with a fresh tree
		destroy_tree(tree);
		tree = NULL;
	// quiz
	} else if (commandIs("quit", command)) {
		// clean up and exit
		destroy_tree(tree);
		freeTokenArray(tokens, argCount);
		free(command);
		exit(EXIT_SUCCESS);
	// invalid command
	} else {
		fprintf(stderr, "Unknown Command: %s\n", command);
	}

	freeTokenArray(tokens, argCount);
}

/*
* main program loop
* input, execute, cleanup, repeat
*/
void entryLoop() {
	char buff[MAX_LINE + 1];\
	char * line;
	printPrompt();
	while ((line = fgets(buff, MAX_LINE, stdin)) != NULL) {
		// trim start and end whitespace
		char * trimmed = trim(line);
		// echo line back to user
		printf("+ %s\n\n", trimmed);

		// gets command in a molloced string
		// trimmed is modefied and inserts spaces
		char * command = getCommand(trimmed);
		// put args into malloced string and free line
		char * commandArgs = trim(line);

		doCommand(command, commandArgs);
		free(command);
		printPrompt();
	}
}

/*
* main program
*
* @param argc  number of command line arguments
* @param argc  command line arguments
* @return exit status
*/
int main(int argc, char * argv[]) {
	// if a file was supplied
	if (argc > 1) {
		// only accepts one file
		if (argc > 2) {
			printUsage();
			return(EXIT_FAILURE);
		// read file
		} else {
			char * filename = argv[1];
			parseFile(filename);
		}
	}
	// start input loop
	entryLoop();
	return EXIT_SUCCESS;
}
