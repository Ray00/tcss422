/*
 * pcb.h
 *
 *  Created on: Jan 6, 2016
 *      Author: nabilfadili
 */

#ifndef PCB_H_
#define PCB_H_

typedef struct pcb_type {
	int id;
	int priority;
} PCB;
typedef PCB *PCB_p;

PCB_p createNewPCB(void);
void setPCB_id(PCB_p p, int id);
int getPCB_id(PCB_p p);
void setPCB_priority(PCB_p p, int priority);
int getPCB_priority(PCB_p p);

#endif /* PCB_H_ */
