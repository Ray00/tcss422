#ifndef PCB_H
#define PCB_H

#include <stdlib.h>

typedef struct pcb {
	int process_num;
	int priority_num;

} PCB;

typedef PCB * PCB_p;

PCB_p pcbConstructor(int pID, int priority);
void pcbDestructor(PCB_p me);

#endif 
