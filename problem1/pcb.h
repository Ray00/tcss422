#ifndef PCB_H_
#define PCB_H_

typedef struct pcb_type {
	int process_num;
	int priority;
} PCB;
typedef PCB *PCB_p;

PCB_p createNewPCB(void);
void setPCB_process_num(PCB_p p, int process_num);
int getPCB_process_num(PCB_p p);
void setPCB_priority(PCB_p p, int priority);
int getPCB_priority(PCB_p p);

#endif /* PCB_H_ */
