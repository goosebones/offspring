/*
* implementation of functions prescribed in tree_node.h
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdlib.h>

#include "tree_node.h"


tree_node_t * create_node(char * name) {
	tree_node_t * n = malloc(sizeof(tree_node_t));
	n->name = name;
	n->children = 0;
	n->offSize = 6;
	tree_node_t ** children = malloc(6 * sizeof(tree_node_t));
	n->offspring = children;
	return NULL;
}

void destroy_tree(tree_node_t * tree) {
	//TODO
}

tree_node_t * find_node(tree_node_t * tree, char * name) {
	//TODO
	return NULL;
}

void print_tree(tree_node_t * tree, char * name) {
	//TODO
}

tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child) {
	if (tree->children == tree->offSize) {
		//realloc
	}
	//TODO
	return NULL;
}
