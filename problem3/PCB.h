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
#include <time.h>

//#define NUMREGS 16
#define MAX_PC 2345

enum state_type {new, ready, running, waiting, halted, interrupted, terminated};

typedef struct pcb_type {
	unsigned int process_num;
	unsigned int priority;      /* extrinsic property */
    enum state_type state;      /* current state */
    unsigned int addressPC;     /* where to resume */
	unsigned int addressSW;
	unsigned int max_pc;
	struct tm * creation;
	struct tm * termination;
	unsigned int terminate;
	unsigned int term_count;
	unsigned int io1_trap[4];
	unsigned int io2_trap[4];
//    int reg_file[NUMREGS];      /* contents of GPRs */
    unsigned int addressSpace;  /* where in memory */
} PCB;
typedef PCB *PCB_p;

/* Prototypes */
PCB_p PCB_constructor(unsigned int, unsigned int, enum state_type, unsigned int, unsigned int);
PCB_p PCB_constructorWithEmpty(void);
void PCB_destructor(PCB_p);
void PCB_setProcessNumber(PCB_p, unsigned int);
unsigned int PCB_getProcessNumber(PCB_p);
void PCB_setPriority(PCB_p, unsigned int);
unsigned int PCB_getPriority(PCB_p);
void PCB_setPC(PCB_p, unsigned int);
unsigned int PCB_getPC(PCB_p);
void PCB_setSW(PCB_p, unsigned int);
unsigned int PCB_getSW(PCB_p);
void PCB_setState(PCB_p, enum state_type);
void PCB_incrementTermCount(PCB_p);
unsigned int PCB_checkTerminate(PCB_p);
void PCB_terminate(PCB_p);
char * PCB_toString(PCB_p);

#endif /* PCB_H_ */
