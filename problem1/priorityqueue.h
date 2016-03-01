/***************************************************************************
* priorityqueue.h
*
* Programming Team:
* Ray Kim
* Kyle Doan
* Nabil Fadili
* Riley Gratzer
*
* Date: 2/12/16
*
****************************************************************************/

#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <stdlib.h>
#include <stdio.h>
#include "fifoqueue.h"
#include "pcb.h"

#define MAX_PRIORITY 3	//NOTE: Only 4 priorities for final project

typedef struct PriorityQueue {
  PCB_QUEUE_STR_p queueArray[MAX_PRIORITY];
  unsigned int size;
} PriorityQueue;

typedef PriorityQueue * PriorityQueue_p;

/* Prototypes */
PriorityQueue_p PriorityQueue_constructor(void);
void PriorityQueue_destructor(PriorityQueue_p);
void PriorityQueue_enqueue(PriorityQueue_p, PCB_p);
PCB_p PriorityQueue_dequeue(PriorityQueue_p);
char * PriorityQueue_toString(PriorityQueue_p);
unsigned int PriorityQueue_size(PriorityQueue_p);

#endif /* PriorityQueue_H_ */
