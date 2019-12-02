/*
* implementation of queue data structure
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdlib.h>

#include "queue.h"
#include "tree_node.h"


/* queue nodes */
typedef struct node {
	void * data;
	struct node * next;
} queueNode;

/* queue struct */
typedef struct queueStruct {
	queueNode * front;
	queueNode * back;
	int size;
} queueStruct;

/*
* create a new node
* @param data  pointer to data
* @return pointer to newly allocated node
*/
static queueNode * node_create(void * data) {
	queueNode * n = malloc(sizeof(queueNode));
	n->data = data;
	n->next = NULL;
	return n;
}

/*
* create a new queue
*/
queueADT que_create() {
	queueStruct * queue = malloc(sizeof(queueStruct));
	queue->front = NULL;
	queue->back = NULL;
	queue->size = 0;
	return queue;
}

/*
* destroy a queue
* free itself and all of its nodes
*/
void que_destroy(queueADT queue) {
	que_clear(queue);
	free(queue);
}

/*
* empty out a queue
* free just its nodes
*/
void que_clear(queueADT queue) {
	queueNode * n = queue->front;
	while (n != NULL) {
		que_dequeue(queue);
		n = queue->front;
	}
}

/*
* add a new node to the back of a queue
*/
void que_enqueue(queueADT queue, void * data) {
	queueNode * newNode = node_create(data);
	// if queue is empty
	if (queue->back == NULL) {
		queue->front = newNode;
	} else {
		queueNode * back = queue->back;
		back->next = newNode;
	}
	queue->back = newNode;
	queue->size++;
}

/*
* removed a node from the front of a queue
*/
void que_dequeue(queueADT queue) {
	// if queue is empty
	if (queue->front == NULL) {
		return;
	}

	queueNode * deq = queue->front;
	queue->front = deq->next;

	if (queue->front == NULL) {
		queue->back = NULL;
	}

	free(deq);
	queue->size--;
}

/*
* return from node of a queue
*/
const void * que_front(const queueADT queue) {
	// if queue is empty
	if (queue->front == NULL) {
		return NULL;
	}
	queueNode * n = queue->front;
	return n->data;
}

/*
* get the size of a queue
*/
size_t que_size(queueADT queue) {
	return queue->size;
}
