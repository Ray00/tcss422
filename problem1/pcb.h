/***************************************************************************
* pcb.h
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

#ifndef PCB_H
#define PCB_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



//#define NUMREGS 16
#define MAX_PC 2345
#define MAX_CALLS_FOR_IO 4

enum state_type {new, ready, running, interrupted, waiting, halted, idle};
enum process_type {io_type, compIntense_type, realistic_type};

typedef struct pcb_type {
    void * childClass;
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
    unsigned int * io_1_array_ptr;
    unsigned int * io_2_array_ptr;
		unsigned int * io_1_traps;
		unsigned int * io_2_traps;
//    int reg_file[NUMREGS];      /* contents of GPRs */
    unsigned int addressSpace;  /* where in memory */

    //NOTE: New for Final Project
    enum process_type processType;
} PCB;
typedef PCB *PCB_p;

/* Prototypes */
PCB_p PCB_constructor(unsigned int, unsigned int, enum state_type, unsigned int, unsigned int, unsigned int, unsigned int);
unsigned int * PCB_create_trap_call_array (unsigned int);
PCB_p PCB_constructorWithEmpty(void);
void PCB_destructor(PCB_p);
void PCB_setProcessNumber(PCB_p, unsigned int);
int PCB_getProcessNumber(PCB_p);
void PCB_setPriority(PCB_p, unsigned int);
int PCB_getPriority(PCB_p);
void PCB_setPC(PCB_p, unsigned int);
int PCB_getPC(PCB_p);
void PCB_setState(PCB_p, enum state_type);
void PCB_terminate(PCB_p);
void PCB_incrementTermCount(PCB_p);
struct tm * PCB_getTimestamp(void);
unsigned int PCB_currPCHasIOCall(PCB_p, unsigned int);
void PCB_toString(PCB_p, char *);

//NOTE: New for final project
void PCB_setProcessType(PCB_p, enum process_type);

#endif /* PCB_H_ */
