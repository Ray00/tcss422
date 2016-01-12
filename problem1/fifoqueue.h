/*
 * fifoqueue.h
 *
 *  Created on: Jan 7, 2016
 *      Author: Ray Kim
 */

#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include "pcb.h"
#include <stdlib.h>
#include <string.h>

//inner class
typedef struct node_str {
	struct node_str * next_node;
	PCB_p pcb_addr;
	
} NODE_STR;

typedef NODE_STR * NODE_STR_p;



//this class
typedef struct pcb_queue_str {
	NODE_STR_p head_node;
	NODE_STR_p tail_node;
	unsigned int num_nodes;
	
} PCB_QUEUE_STR;

typedef PCB_QUEUE_STR * PCB_QUEUE_STR_p;

//prototypes
NODE_STR_p nodeConstructor(PCB_p);
void nodeDestructor(NODE_STR_p);

PCB_QUEUE_STR_p queueConstructor(void);
int queueDestructor(PCB_QUEUE_STR_p);
int enqueue(PCB_QUEUE_STR_p, PCB_p);
NODE_STR_p dequeue(PCB_QUEUE_STR_p);

PCB_p getPCB(NODE_STR_p);

char * queue_toString(PCB_QUEUE_STR_p);

#endif 
