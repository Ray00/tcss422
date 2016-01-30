/*
 * pcb.c
 *
 *  Created on: Jan 7, 2016
 *      Author: Kyle Doan, nabilfadili
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
	result->priority = -1;
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
 * Function:  PCB_setPC
 * --------------------
 * Sets the passed PCB object's PC address field to the passed addressPC.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated priority.
 */
void PCB_setPC (PCB_p self, unsigned int pc) {
    self->addressPC = pc;
}

/*
 * Function:  PCB_getPC
 * --------------------
 * Gets the passed PCB object's PC address.
 *
 *  returns: The PCB object's PC address.
 */
int PCB_getPC (PCB_p self) {
    return self->addressPC;
}

void PCB_setState (PCB_p self, enum state_type s) {
    self->state = s;
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
     char state_description[16];
     //find correct string to print for state enum
     //new, ready, running, interrupted, waiting, halted, idle
     switch (me->state) {
         case 0:
             strcpy(state_description, "new");
             break;
         case 1:
             strcpy(state_description, "ready");
             break;
         case 2:
             strcpy(state_description, "running");
             break;
         case 3:
             strcpy(state_description, "interrupted");
             break;
         case 4:
             strcpy(state_description, "waiting");
             break;
         case 5:
             strcpy(state_description, "halted");
             break;
         default:
             strcpy(state_description, "idle");
             break;
     }
     
     char * result = (char *) malloc(sizeof(char) * 1000);
     sprintf(result, "content: PCB_ID: %d, Priority: %d, State: %s, PC: 0x%04X\n",
             me->process_num, me->priority, state_description, me->addressPC);
     return result;
 }
