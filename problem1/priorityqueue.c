#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "priorityqueue.h"
#include "fifoqueue.h"
#include "pcb.h"


// Constructs a PriorityQueue

PriorityQueue_p PriorityQueue_constructor(void) {
    PriorityQueue_p prioQ = (PriorityQueue_p) malloc(sizeof(PriorityQueue));
    //If not NULL
    if (prioQ != NULL) {
        int i = 0;
        for (i = 0; i < 16; i++) {
            prioQ->queueArray[i] = FIFO_constructor();
        }
    //Return NULL if NULL
    } else {
        return NULL;
    }
    //Return Priority Queue Pointer
    return prioQ;
}

// Destructs PriorityQueue
// *To be implemented

void PriorityQueue_destructor(PriorityQueue_p this) {
  free(this);
}

// Add a process to the PriorityQueue
void priority_enqueue(PriorityQueue_p this, PCB_p pcb_p) {
	unsigned int priorityLevel = pcb_p->priority;
	PCB_QUEUE_STR_p priorityPointer = this->queueArray[priorityLevel];
	FIFO_enqueue(priorityPointer, pcb_p);
    return;
}

// Removes process based on priority in PriorityQueue
PCB_p priority_dequeue(PriorityQueue_p this) {
	PCB_p temp = NULL;
	int i = 0;

	for (i = 0; i < 16; i++) {
		temp = FIFO_dequeue(this->queueArray[i]);
		if (temp != NULL) {
            return temp;
		}
	}
  return NULL;
}

// toString for PriorityQueue
char * PriorityQueue_toString(PriorityQueue_p this) {
    char * result = (char *) malloc(sizeof(char) * 16000);
    char * temp = (char *) malloc(sizeof(char) * 1000);
    int i = 0;
    for (i = 0; i < 16; i++) {
        temp = FIFO_toString(this->queueArray[i]);
        strcat(result, temp);
        strcat(result, "\n");
    }
    return result;
}