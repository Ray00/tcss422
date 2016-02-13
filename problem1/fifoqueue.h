/***************************************************************************
* fifoqueue.h
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

#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include <stdlib.h>
#include <string.h>
#include "pcb.h"

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
    NODE_STR_p free_node;

} PCB_QUEUE_STR;

typedef PCB_QUEUE_STR * PCB_QUEUE_STR_p;

//prototypes
NODE_STR_p NODE_constructor(PCB_p);
void NODE_destructor(NODE_STR_p);

PCB_QUEUE_STR_p FIFO_constructor(void);
int FIFO_destructor(PCB_QUEUE_STR_p);
int FIFO_enqueue(PCB_QUEUE_STR_p, PCB_p);
PCB_p FIFO_dequeue(PCB_QUEUE_STR_p);
unsigned int FIFO_size(PCB_QUEUE_STR_p);

char * FIFO_toString(PCB_QUEUE_STR_p, char *);

#endif
