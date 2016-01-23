/*
 * pcb_test.h
 *
 *  Created on: Jan 9, 2016
 *      Author: Kyle Doan, nabilfadili
 */

#ifndef PCB_H
#define PCB_H

#include <stdlib.h>
#include <stdio.h>

//#define NUMREGS 16

enum state_type {new, ready, running, blocked, waiting, halted};

typedef struct pcb_type {
	unsigned int process_num;
	unsigned int priority;      /* extrinsic property */
    enum state_type state;      /* current state */
    unsigned int addressPC;     /* where to resume */
//    int reg_file[NUMREGS];      /* contents of GPRs */
    unsigned int addressSpace;  /* where in memory */
} PCB;
typedef PCB *PCB_p;

/* Prototypes */
PCB_p PCB_constructor(unsigned int, unsigned int, enum state_type, unsigned int, unsigned int);
PCB_p PCB_constructorWithEmpty(void);
void PCB_destructor(PCB_p);
void PCB_setProcessNumber(PCB_p, unsigned int);
int PCB_getProcessNumber(PCB_p);
void PCB_setPriority(PCB_p, unsigned int);
int PCB_getPriority(PCB_p);
char * PCB_toString(PCB_p);

#endif /* PCB_H_ */
