/*
* implementation of queue data structure
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdlib.h>

#include "queue.h"
#include "tree_node.h"

typedef struct queueStruct {
	bool (*equal)();
	tree_node_t * front;
	tree_node_t * back;
} queueStruct;
