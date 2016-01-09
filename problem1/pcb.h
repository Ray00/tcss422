#ifndef PCB_H
#define PCB_H

#include <stdlib.h>
#include <stdio.h>

enum state_type {new, ready, running, waiting, halted};

typedef struct pcb_type {
	int process_num;
	int priority_num;
    enum state_type state;
    int addressPC;
    int addressSpace;
} PCB;
typedef PCB *PCB_p;

/* Prototypes */
PCB_p PCB_constructor(int, int, enum state_type, int, int);
void PCB_destructor(PCB_p);
void PCB_setProcessNumber(PCB_p, int);
int PCB_getProcessNumber(PCB_p);
void PCB_setPriority(PCB_p, int);
int PCB_getPriority(PCB_p);
char * PCB_toString(PCB_p);

#endif /* PCB_H_ */
