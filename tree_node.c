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

#define INIT_CHILDREN_COUNT 3

tree_node_t * create_node(char * name) {
	tree_node_t * n = malloc(sizeof(tree_node_t));
	n->name = malloc(strlen(name) * sizeof(char));
	strcpy(n->name, name);
	n->children = 0;
	n->offSize = INIT_CHILDREN_COUNT;
	tree_node_t ** offspring = malloc(INIT_CHILDREN_COUNT * sizeof(tree_node_t));
	n->offspring = offspring;
	return n;
}

void destroy_tree(tree_node_t * tree) {
	if (tree == NULL) {
		return;
	}
	for (int i = 0; i < tree->children; i++) {
		tree_node_t * childNode = tree->offspring[i];
		destroy_tree(childNode);
	}
	free(tree->name);
	free(tree->offspring);
	free(tree);
}

void print_offspring_line(tree_node_t * treeNode) {
	printf("%s had ", treeNode->name);
	if (treeNode->children == 0) {
		printf("no offspring");
	} else if (treeNode->children == 1) {
		tree_node_t * childNode = treeNode->offspring[0];
		printf("%s", childNode->name);
	} else if (treeNode->children == 2) {
		tree_node_t * childNode1 = treeNode->offspring[0];
		tree_node_t * childNode2 = treeNode->offspring[1];
		printf("%s and %s", childNode1->name, childNode2->name);
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

tree_node_t * find_node(tree_node_t * tree, char * name) {
	if (tree == NULL) {
		return NULL;
	}
	queueADT queue = que_create();
	que_enqueue(queue, tree);
	while(que_size(queue) > 0) {
		//queueNode * queueNode = (queueNode*)que_front(queue);
		//tree_node_t * treeNode = (tree_node_t*)queueNode->data;
		tree_node_t * treeNode = (tree_node_t*)que_front(queue);
		que_dequeue(queue);
		//TODO idk what is happening here
		if ((strcmp(treeNode->name, name) == 0) || (strcmp(name, "") == 0)) {
			return treeNode;
		} else {
			for (int i = 0; i < treeNode->children; i++) {
				que_enqueue(queue, treeNode->offspring[i]);
			}
		}
	}
	return NULL;
}

void print_tree(tree_node_t * tree, char * name) {
	if (tree == NULL) {
		fprintf(stderr, "Error: tree is empty.\n");
		return;
	}
	if (find_node(tree, name) == NULL) {
		fprintf(stderr, "Error: '%s' not found.\n", name);
		return;
	}
	queueADT queue = que_create();
	que_enqueue(queue, tree);
	while(que_size(queue) > 0) {
		//queueNode * queueNode = (queueNode*)que_front(queue);
		//tree_node_t * treeNode = (tree_node_t*)queueNode->data;
		tree_node_t * treeNode = (tree_node_t*)que_front(queue);
		que_dequeue(queue);
		//int nameLength = strlen(node->name);
		if ((strcmp(treeNode->name, name) == 0) || (strcmp(name, "") == 0)) {
			print_offspring_line(treeNode);
			for (int i = 0; i < tree->children; i++) {
				tree_node_t * childNode = tree->offspring[i];
				print_tree(childNode, childNode->name);
			}
		} else {
			for (int i = 0; i < tree->children; i++) {
				//que_enqueue(queue, tree->offspring[i]);
				print_tree(tree->offspring[i], name);
			}
		}
	}
}

void insert_offspring(tree_node_t * parentNode, tree_node_t * childNode) {
	if (parentNode->children == parentNode->offSize) {
		// realloc
		int oldSize = parentNode->offSize;
		int newSize = oldSize + 2;

		tree_node_t ** oldOffspring = parentNode->offspring;
		tree_node_t ** newOffspring = realloc(oldOffspring, newSize * sizeof(tree_node_t));
		parentNode->offspring = newOffspring;
	}
	parentNode->offspring[parentNode->children] = childNode;
	parentNode->children = parentNode->children + 1;
}

tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child_name) {
	if (tree == NULL) {
		tree_node_t * newRoot = create_node(parent_name);
		tree_node_t * childNode = create_node(child_name);
		insert_offspring(newRoot, childNode);
		return newRoot;
	}

	tree_node_t * parentNode = find_node(tree, parent_name);
	if (parentNode == NULL) {
		if (strcmp(tree->name, child_name) == 0) {
			tree_node_t * newRoot = create_node(parent_name);
			insert_offspring(newRoot, tree);
			return tree;
		} else {
			fprintf(stderr, "Error: %s not found in tree and %s is not the root.", parent_name, child_name);
			return tree;
		}
	} else {
		for (int i = 0; i < parentNode->children; i++) {
			tree_node_t * currentChildNode = parentNode->offspring[i];
			char * currentChildName = currentChildNode->name;
			if (strcmp(currentChildName, child_name) == 0) {
				fprintf(stderr, "Error: %s is already a child of %s.", child_name, parent_name);
				return tree;
			}
		}
		tree_node_t * newChild = create_node(child_name);
		insert_offspring(parentNode, newChild);
		return tree;
	}
	return NULL;
}



int get_tree_size(tree_node_t * treeNode) {
	int size = 1;
	for (int i = 0; i < treeNode->children; i++) {
		size += get_tree_size(treeNode->offspring[i]);
	}
	return size;
}
