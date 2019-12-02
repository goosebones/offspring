/*
* implementation of functions prescribed in tree_node.h
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "tree_node.h"
#include "queue.h"

// initial size of offspring array
#define INIT_CHILDREN_COUNT 3

/*
* create a new tree_node_t
*/
tree_node_t * create_node(char * name) {
	tree_node_t * n = malloc(sizeof(tree_node_t));
	n->name = malloc(strlen(name) * sizeof(char) + 1);
	strcpy(n->name, name);
	n->children = 0;
	n->offSize = INIT_CHILDREN_COUNT;
	tree_node_t ** offspring = malloc(INIT_CHILDREN_COUNT * sizeof(tree_node_t));
	n->offspring = offspring;
	return n;
}

/*
* free a tree and its offspring
*/
void destroy_tree(tree_node_t * tree) {
	if (tree == NULL) {
		return;
	}
	// free each offspring
	for (int i = 0; i < tree->children; i++) {
		tree_node_t * childNode = tree->offspring[i];
		// recurse down entire tree
		destroy_tree(childNode);
	}
	free(tree->name);
	free(tree->offspring);
	free(tree);
}

/*
* print formatted version of tree_node_t
*/
void print_offspring_line(tree_node_t * treeNode) {
	// starter
	printf("%s had ", treeNode->name);
	// no offspring
	if (treeNode->children == 0) {
		printf("no offspring");
	// one offspring, no comma or and
	} else if (treeNode->children == 1) {
		tree_node_t * childNode = treeNode->offspring[0];
		printf("%s", childNode->name);
	// two offspring, use 'and'
	} else if (treeNode->children == 2) {
		tree_node_t * childNode1 = treeNode->offspring[0];
		tree_node_t * childNode2 = treeNode->offspring[1];
		printf("%s and %s", childNode1->name, childNode2->name);
	// three+ offspring, use commas with 'and'
	} else {
		for (int i = 0; i < treeNode->children; i++) {
			tree_node_t * childNode = treeNode->offspring[i];
			printf("%s", childNode->name);
			if (i < (treeNode->children - 2)) {
				printf(", ");
			} else if (i < (treeNode->children - 1)) {
				printf(" and ");
			} else {
				;
			}
		}
	}
	printf(".\n");
}

/*
* locate a person in a tree
* return NULL if not found
*/
tree_node_t * find_node(tree_node_t * tree, char * name) {
	// unable to locate
	if (tree == NULL) {
		return NULL;
	}
	// start BFS
	queueADT queue = que_create();
	que_enqueue(queue, tree);
	while(que_size(queue) > 0) {
		tree_node_t * treeNode = (tree_node_t*)que_front(queue);
		que_dequeue(queue);
		// if person is found
		if ((strcmp(treeNode->name, name) == 0) || (strcmp(name, "") == 0)) {
			que_destroy(queue);
			return treeNode;
		} else {
			// keep going therough each offspring
			for (int i = 0; i < treeNode->children; i++) {
				que_enqueue(queue, treeNode->offspring[i]);
			}
		}
	}
	// cleanup
	que_destroy(queue);
	return NULL;
}

/*
* helper function to print_tree()
* used to print out the formatted version of each offspring node
*
* @param tree  tree_node to print out
*/
static void print_tree_help(tree_node_t * tree) {
	// print formatted line for each person
	for (int i = 0; i < tree->children; i++) {
		tree_node_t * childNode = tree->offspring[i];
		print_offspring_line(childNode);
	}
	// recurse on each offspring
	for (int j = 0; j < tree->children; j++) {
		tree_node_t * childNode2 = tree->offspring[j];
		print_tree_help(childNode2);
	}
}

/*
* print out a person in the tree
* prints out everything below specified person
*/
void print_tree(tree_node_t * tree, char * name) {
	// invalid print
	if (tree == NULL) {
		fprintf(stderr, "error: '%s' not found.\n", name);
		return;
	}
	// person is not in tree
	if (find_node(tree, name) == NULL) {
		fprintf(stderr, "error: '%s' not found.\n", name);
		return;
	}
	// start BFS
	queueADT queue = que_create();
	que_enqueue(queue, tree);
	while(que_size(queue) > 0) {
		tree = (tree_node_t*)que_front(queue);
		que_dequeue(queue);
		// if person is found
		if ( (strcmp(tree->name, name) == 0) || (strcmp(name, "") == 0)) {
			print_offspring_line(tree);
			print_tree_help(tree);
		} else {
			// keep going through each offspring
			for (int i = 0; i < tree->children; i++) {
				tree_node_t * childNode = tree->offspring[i];
				que_enqueue(queue, childNode);
			}
		}
	}
	// cleanup
	que_destroy(queue);
}

/*
* give a parent node a new offspring
* helper function to add_child()
* will reallocate memory if necessary
*
* @param parentNode  parent node to give offspring to
* @param childNode  child node to add
*/
static void insert_offspring(tree_node_t * parentNode, tree_node_t * childNode) {
	// check if realloc is needed
	if (parentNode->children == parentNode->offSize) {
		int oldSize = parentNode->offSize;
		// 2 extra slots added
		int newSize = oldSize + 2;
		tree_node_t ** oldOffspring = parentNode->offspring;
		tree_node_t ** newOffspring = realloc(oldOffspring, newSize * sizeof(tree_node_t));
		parentNode->offspring = newOffspring;
	}
	parentNode->offspring[parentNode->children] = childNode;
	parentNode->children = parentNode->children + 1;
}

/*
* add a child to a parent
*/
tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child_name) {
	// if tree does not yet exist, create new one
	if (tree == NULL) {
		tree_node_t * newRoot = create_node(parent_name);
		tree_node_t * childNode = create_node(child_name);
		insert_offspring(newRoot, childNode);
		return newRoot;
	}

	tree_node_t * parentNode = find_node(tree, parent_name);
	// parent is not found
	if (parentNode == NULL) {
		// child is root of tree
		// parent becomes new root
		if (strcmp(tree->name, child_name) == 0) {
			tree_node_t * newRoot = create_node(parent_name);
			insert_offspring(newRoot, tree);
			return newRoot;
		// error
		} else {
			fprintf(stderr, "error: '%s' is not in the tree and '%s' is not the root.\n", parent_name, child_name);
			return tree;
		}
	// parent is found
	} else {
		// check to make sure child isn't aleady present
		for (int i = 0; i < parentNode->children; i++) {
			tree_node_t * currentChildNode = parentNode->offspring[i];
			char * currentChildName = currentChildNode->name;
			if (strcmp(currentChildName, child_name) == 0) {
				fprintf(stderr, "error: '%s' is already a child of '%s'.\n", child_name, parent_name);
				return tree;
			}
		}
		// okay to add child
		tree_node_t * newChild = create_node(child_name);
		insert_offspring(parentNode, newChild);
		return tree;
	}
	// error
	return NULL;
}

/*
* get the size of a tree
* calculates the number of nodes from a starting position
* @param treeNode  starting tree_node
* @return number of nodes in tree from start node
*/
int get_tree_size(tree_node_t * treeNode) {
	int size = 1;
	for (int i = 0; i < treeNode->children; i++) {
		size += get_tree_size(treeNode->offspring[i]);
	}
	return size;
}

/*
* helper function to get_tree_height()
*
* @param treeNode  node to start searchin from
* @return largest height found from a search
*/
static int height_helper(tree_node_t * treeNode) {
	int maxDepth = 0;
	for (int i = 0; i < treeNode->children; i++) {
		int newDepth = height_helper(treeNode->offspring[i]);
		maxDepth = (maxDepth > newDepth ? maxDepth : newDepth);
	}
	return maxDepth + 1;

}

/*
* get the height of a tree
* starts at a node and seaches down through offspring
*
* @param treeNode  starting node to search from
* @return longest offspring chain in tree from starting node
*/
int get_tree_height(tree_node_t * treeNode) {
	if (treeNode == NULL) {
		return -1;
	}
	int height = height_helper(treeNode);
	return height - 1;
}
