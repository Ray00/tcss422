/*
 * cpu.h
 *
 *  Created on: Jan 22, 2016
 *      Author: nabilfadili
 */

#ifndef CPU_H_
#define CPU_H_

#include "pcb.h"
#include "fifoqueue.h"

typedef struct cpu_type {
	unsigned int pc;
	unsigned int sysStack;
	PCB_p currentProcess;
	PCB_QUEUE_STR_p readyQueue;					//fifoqueue
	PCB_QUEUE_STR_p createdQueue;				//fifoqueue
	PCB_QUEUE_STR_p terminatedQueue;			//fifoqueue
} CPU;
typedef CPU *CPU_p;

enum interrupt_type {timer, io};

/*Construction Prototypes*/
CPU_p CPU_constructor(void);					//Instantiates CPU struct, including all the queues
void CPU_destructor(CPU_p);						//Free's all memory related to the passed CPU object
void CPU_setPC(CPU_p, unsigned int);			//pc setter
unsigned int CPU_getPC(CPU_p);					//pc getter
void CPU_SysStack_push(CPU_p, unsigned int);	//Not really a "push", just overwrites
unsigned int CPU_SysStack_pop(CPU_p);			//Not really a "pop", just gets the current value
void CPU_setCurrentProcess(CPU_p, PCB_p);		//Current PCB setter
PCB_p CPU_getCurrentProcess(CPU_p);				//Current PCB getter
void CPU_readyQueue_enqueue(CPU_p, PCB_p);		//RQ_enqueue - readyQueue
PCB_p CPU_readyQueue_dequeue(CPU_p);			//RQ_dequeue - readyQueue
void CPU_createdQueue_enqueue(CPU_p, PCB_p);	//CQ_enqueue - queue of newly created PCB's
PCB_p CPU_createdQueue_dequeue(CPU_p);			//CQ_dequeue - queue of newly created PCB's
void CPU_terminatedQueue_enqueue(CPU_p, PCB_p);	//TQ_enqueue - queue of terminated PCB's
PCB_p CPU_terminatedQueue_dequeue(CPU_p);		//TQ_dequeue - queue of terminated PCB's

/*Function Prototypes*/
void CPU_interruptServiceRoutine(CPU_p);
	//1.) Change the state of the running process to interrupted,
	//2.) Save the CPU state to the PCB for that process (PC value)
	//3.) Upcall to scheduler
	//4.) Put PC value from sysStack into pc
	//5.) Return

void CPU_scheduler(CPU_p, interrupt_type);
	//1.) Put the process back into the ready queue
	//2.) Change its state from interrupted to ready
	//3.) Upcall to dispatcher
	//4.) Return - Chance to do more before returning but nothing yet

void CPU_dispatcher(CPU_p);
	//1.) Save the state of the current process into its PCB (here we mean the PC value)
	//2.) Dequeue the next waiting process (PCB)
	//3.) Change its state to running
	//4.) Copy its PC value (and SW if you implement it) to the SysStack location to replace the PC of the interrupted process
	//5.) Return

char* CPU_toString(CPU_p);

#endif /* CPU_H_ */
