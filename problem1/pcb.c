#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

/*
 * Function:  createNewPCB
 * --------------------
 * constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  returns: 	PCB_p pointer to the PCB object in the heap
 */
PCB_p createNewPCB(void) {
	PCB_p newPCB = (PCB_p) malloc(sizeof(struct pcb_type));
	return newPCB;
}

void destroyPCB(PCB_p p) {
	free(p);
}

void setPCB_process_num(PCB_p p, int process_num) {
	p->process_num = process_num;
}

int getPCB_process_num(PCB_p p) {
	return p->process_num;
}

void setPCB_priority(PCB_p p, int priority) {
	p->priority = priority;
}

int getPCB_priority(PCB_p p) {
	return p->priority;
}
