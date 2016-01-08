#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

/*
 * Function:  PCB_constructor
 * --------------------
 * Constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  returns: PCB_p pointer to the PCB object in the heap
 */
PCB_p PCB_constructor(void) {
	PCB_p newPCB = (PCB_p) malloc(sizeof(struct pcb_type));
	return newPCB;
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
void PCB_setProcessNumber(PCB_p p, int process_num) {
	p->process_num = process_num;
}

/*
 * Function:  PCB_getProcessNumber
 * --------------------
 * Gets the passed PCB object's process number.
 *
 *  returns: The PCB object's process_num.
 */
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
void PCB_setPriority(PCB_p p, int priority) {
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
void PCB_toString(PCB_p p) {
	printf("PCB process number: %d\nPCB priority: %d\n", p->process_num, p->priority);
}
