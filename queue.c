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
} queueNode;

typedef struct queueStruct {
	queueNode * front;
	queueNode * back;
	int size;
} queueStruct;

queueNode * node_create(void * data) {
	queueNode * n = malloc(sizeof(queueNode));
	n->data = data;
	n->next = NULL;
	return n;
}

queueADT que_create() {
	queueStruct * queue = malloc(sizeof(queueStruct));
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
	queueNode * n = queue->front;
	while (n != NULL) {
		que_dequeue(queue);
	}
}

void que_enqueue(queueADT queue, void * data) {
	queueNode * newNode = node_create(data);

	if (queue->back == NULL) {
		queue->front = newNode;
	} else {
		queueNode * back = queue->back;
		back->next = newNode;
	}
	queue->back = newNode;
	queue->size++;
}

void que_dequeue(queueADT queue) {
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

const void * que_front(const queueADT queue) {
	if (queue->front == NULL) {
		return NULL;
	}
	queueNode * n = queue->front;
	return n->data;
}

size_t que_size(queueADT queue) {
	return queue->size;
}
