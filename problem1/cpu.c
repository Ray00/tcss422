/*
 * cpu.c
 *
 *  Created on: Jan 22, 2016
 *      Author: nabilfadili
 */

#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

CPU_p CPU_constructor(void) {
	CPU_p newCPU = (CPU_p) malloc(sizeof(CPU));
	newCPU->pc = 0;
	newCPU->sysStack = 0;
	newCPU->currentProcess = NULL;
	newCPU->readyQueue = FIFO_constructor();
	newCPU->createdQueue = FIFO_constructor();
	newCPU->terminatedQueue = FIFO_constructor();
	return newCPU;
}

void CPU_destructor(CPU_p self) {
	free(self);
}

void CPU_setPC(CPU_p self, unsigned int pc) {
	self->pc = pc;
}

unsigned int CPU_getPC(CPU_p self) {
	return self->pc;
}

void CPU_SysStack_push(CPU_p, unsigned int);				//Not really a "push", just overwrites
unsigned int CPU_SysStack_pop(CPU_p);					//Not really a "pop", just gets the current value
void CPU_setCurrentProcess(CPU_p, PCB_p);		//Current PCB setter
PCB_p CPU_getCurrentProcess(CPU_p);				//Current PCB getter
void CPU_readyQueue_enqueue(CPU_p, PCB_p);		//RQ_enqueue - readyQueue
PCB_p CPU_readyQueue_dequeue(CPU_p);			//RQ_dequeue - readyQueue
void CPU_createdQueue_enqueue(CPU_p, PCB_p);	//CQ_enqueue - queue of newly created PCB's
PCB_p CPU_createdQueue_dequeue(CPU_p);			//CQ_dequeue - queue of newly created PCB's
void CPU_terminatedQueue_enqueue(CPU_p, PCB_p);	//TQ_enqueue - queue of terminated PCB's
PCB_p CPU_terminatedQueue_dequeue(CPU_p);		//TQ_dequeue - queue of terminated PCB's
char* CPU_toString(CPU_p self) {
	char * result = (char *) malloc(sizeof(char) * 1000);
	sprintf(result, "Current PC: %u\nCurrent sysStack: %d\nCurrent Process: \n"
			"ReadyQueue Size: \nCreatedQueue Size: \nTerminatedQueue Size: \n", self->pc, self->sysStack);
	return result;
}

int main() {
	CPU_p testCPU = CPU_constructor();
	printf(CPU_toString(testCPU));

	unsigned int testPC = 3000;
	CPU_setPC(testCPU, testPC);
	printf("\nsetPC Test: %u", CPU_getPC(testCPU));


	exit(0);
}

