/*
 * pcb.c
 *
 *  Created on: Jan 7, 2016
 *      Author: Kyle Doan, nabilfadili
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

/*
 * Function:  PCB_constructor
 * --------------------
 * Constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  params:  pID processID
 *			 priority
 *			 s
 *			 addPC
 *			 addSp
 *  returns: PCB_p pointer to the PCB object in the heap
 */
PCB_p PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSp) {
    PCB_p result = (PCB_p) malloc(sizeof(PCB));
    if (result != (PCB_p) NULL) {
        result->process_num = pID;
        result->priority = priority;
        result->state = s;
        result->addressPC = addPC;
        result->addressSpace = addSp;
    }
    return result;
}

PCB_p PCB_constructorWithEmpty() {
	PCB_p result = (PCB_p) malloc(sizeof(PCB));
	return result;
}

/*
 * Function:  PCB_destructor
 * --------------------
 * Deallocates the memory being used by the passed PCB pointer.
 *
 *  params: PCB_p pointer to the PCB object in the heap
 */
void PCB_destructor(PCB_p p) {
	free(p);
}

/*
 * Function:  PCB_setProcessNumber
 * --------------------
 * Sets the passed PCB object's process_num field to the passed process number.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated process number.
 */
void PCB_setProcessNumber(PCB_p p, unsigned int process_num) {
	p->process_num = process_num;
}

int PCB_getProcessNumber(PCB_p p) {
	return p->process_num;
}

/*
 * Function:  PCB_setPriority
 * --------------------
 * Sets the passed PCB object's priority field to the passed priority.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated priority.
 */
void PCB_setPriority(PCB_p p, unsigned int priority) {
	p->priority = priority;
}

/*
 * Function:  PCB_getPriority
 * --------------------
 * Gets the passed PCB object's priority.
 *
 *  returns: The PCB object's priority.
 */
int PCB_getPriority(PCB_p p) {
	return p->priority;
}

/*
 * Function:  PCB_toString
 * --------------------
 * Prints relevant information about the PCB object to the console for
 * testing/debugging purposes.
 *
 * params:	PCB_p pointer to the PCB object in the heap.
 */
 char* PCB_toString(PCB_p me) {
     char * result = (char *) malloc(sizeof(char) * 1000);
     sprintf(result, "content: PID: %d, Priority: %d, State: %d, PC: 0x%04X, etc.\n",
             me->process_num, me->priority, me->state, me->addressPC);
     return result;
 }
