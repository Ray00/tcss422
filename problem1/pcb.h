#ifndef PCB_H_
#define PCB_H_

typedef struct pcb_type {
	int process_num;
	int priority;
} PCB;
typedef PCB *PCB_p;

PCB_p PCB_constructor(void);
void PCB_destructor(PCB_p p);
void PCB_setProcessNumber(PCB_p p, int process_num);
int PCB_getProcessNumber(PCB_p p);
void PCB_setPriority(PCB_p p, int priority);
int PCB_getPriority(PCB_p p);
void PCB_toString(PCB_p p);

#endif /* PCB_H_ */
