/*
 * pcb.c
 *
 *  Created on: Jan 6, 2016
 *      Author: nabilfadili
 */

#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

PCB_p createNewPCB(void) {
	PCB_p newPCB = (PCB_p) malloc(sizeof(struct pcb_type));
	//if (newPCB == NULL) {printf("Not enough memory");}
	return newPCB;
}

void setPCB_id(PCB_p p, int id) {
	p->id = id;
}

int getPCB_id(PCB_p p) {
	return p->id;
}

void setPCB_priority(PCB_p p, int priority) {
	p->priority = priority;
}

int getPCB_priority(PCB_p p) {
	return p->priority;
}



