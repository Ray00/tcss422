#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <stdlib.h>
#include <stdio.h>
#include "fifoqueue.h"
#include "pcb.h"

typedef struct PriorityQueue {
  PCB_QUEUE_STR_p queueArray[16];
} PriorityQueue;

typedef PriorityQueue * PriorityQueue_p;

/* Prototypes */
PriorityQueue_p PriorityQueue_constructor(void);
void PriorityQueue_destructor(PriorityQueue_p);
void priority_enqueue(PriorityQueue_p, PCB_p);
PCB_p priority_dequeue(PriorityQueue_p);
char * PriorityQueue_toString(PriorityQueue_p);

#endif /* PriorityQueue_H_ */
