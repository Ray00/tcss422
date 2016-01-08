#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

/*
 * Function:  createNewPCB
 * --------------------
 * Constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  returns: 	PCB_p pointer to the PCB object in the heap
 */
PCB_p createNewPCB(void) {
	PCB_p newPCB = (PCB_p) malloc(sizeof(struct pcb_type));
	return newPCB;
}

/*
 * Function:  destroyPCB
 * --------------------
 * Deallocates the memory being used by the passed PCB pointer.
 *
 *  params: 	PCB_p pointer to the PCB object in the heap
 */
void destroyPCB(PCB_p p) {
	free(p);
}


/*
 * Function:  setPCB_process_num
 * --------------------
 * Sets the passed PCB object's process_num field to the passed process number.
 *
 *  params: 	PCB_p pointer to the PCB object in the heap and the designated process number.
 */
void setPCB_process_num(PCB_p p, int process_num) {
	p->process_num = process_num;
}

/*
 * Function:  getPCB_process_num
 * --------------------
 * Gets the passed PCB object's process number.
 *
 *  returns: 	The PCB object's process_num.
 */
int getPCB_process_num(PCB_p p) {
	return p->process_num;
}

/*
 * Function:  setPCB_priority
 * --------------------
 * Sets the passed PCB object's priority field to the passed priority.
 *
 *  params: 	PCB_p pointer to the PCB object in the heap and the designated priority.
 */
void setPCB_priority(PCB_p p, int priority) {
	p->priority = priority;
}

/*
 * Function:  getPCB_priority
 * --------------------
 * Gets the passed PCB object's priority.
 *
 *  returns: 	The PCB object's priority.
 */
int getPCB_priority(PCB_p p) {
	return p->priority;
}
