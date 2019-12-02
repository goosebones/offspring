/*
* queue datastructure ADT
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

// opaque queue datastruct
typedef struct queueStruct * queueADT;

/*
* create a new queue
* queue will be dynamically allocated in memory
*/
queueADT que_create();

/*
* free a queue and its content from memory
*
* @param queue  target queue to free
*/
void que_destroy(queueADT queue);

/*
* empty out the contents of a queue
* contents are freed from memory
*
*@param queue  target queue to empty
*/
void que_clear(queueADT queue);

/*
* add a new element to the end of a queue
* element is allocated in memory
*
* @param queue target queue to add to
* @param data  element to add to queue
*/
void que_enqueue(queueADT queue, void * data);

/*
* remove an element from the front of a queue
* element is freed from memory
*
* @param queue  target queue to remove from
*/
void que_dequeue(queueADT queue);

/*
* peek at the front of a queue
*
* @param queue  target queue to peek
* @return pointer to data
*/
const void * que_front(const queueADT queue);

/*
* get the number of elements in a queue
*
* @param queue  target queue to size
* @return number of elements in queue
*/
size_t que_size(queueADT queue);
