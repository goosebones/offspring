/*
* queue ADT
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

#include <stdbool.h>

typedef struct queueStruct * queueADT;

queueADT que_create();

void que_destroy(queueADT queue);

void que_clear(queueADT queue);

void que_enqueue(queueADT queue, void * data);

void que_dequeue(queueADT queue);

const void * que_front(const queueADT queue);

size_t que_size(queueADT queue);
