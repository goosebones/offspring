/*
* implementation of queue data structure
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdlib.h>

#include "queue.h"
#include "tree_node.h"

typedef struct node {
	void * data;
	struct node * next;
} node;

typedef struct queueStruct {
	bool (*equal)();
	void * front;
	void * back;
	int size;
} queueStruct;

node * node_create(void * data) {
	node * n = malloc(sizeof(node));
	n->data = data;
	n->next = NULL;
	return n;
}

queueADT que_create(bool (*equiv)(void * item1, void * item2)) {
	queueStruct * queue = malloc(sizeof(queueStruct));
	queue->equal = equiv;
	queue->front = NULL;
	queue->back = NULL;
	queue->size = 0;
	return queue;
}

void que_destroy(queueADT queue) {
	que_clear(queue);
	free(queue);
}

void que_clear(queueADT queue) {
	node * n = queue->front;
	while (n != NULL) {
		que_dequeue(queue);
	}
}

void que_enqueue(queueADT queue, void * data) {
	node * newNode = node_create(data);

	if (queue->back == NULL) {
		queue->front = newNode;
		queue->back = newNode;
	} else {
		node * back = queue->back;
		back->next = newNode;
		back = newNode;
	}
	queue->size++;
}

void que_dequeue(queueADT queue) {
	if (queue->front == NULL) {
		return;
	}

	node * deq = queue->front;
	queue->front = deq->next;

	if (queue->front == NULL) {
		queue->back = NULL;
	}

	free(deq);
	queue->size--;
}

const void * que_front(const queueADT queue) {
	return queue->front;
}

size_t que_size(queueADT queue) {
	return queue->size;
}
