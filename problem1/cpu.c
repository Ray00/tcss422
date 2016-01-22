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

void CPU_SysStack_push(CPU_p self, unsigned int pc) {
	self->sysStack = pc;
}

unsigned int CPU_SysStack_pop(CPU_p self) {
	return self->sysStack;
}

void CPU_setCurrentProcess(CPU_p self, PCB_p pcb) {
	self->currentProcess = pcb;
}

PCB_p CPU_getCurrentProcess(CPU_p self) {
	return self->currentProcess;
}

void CPU_readyQueue_enqueue(CPU_p self, PCB_p pcb) {
	FIFO_enqueue(self->readyQueue, pcb);
}

PCB_p CPU_readyQueue_dequeue(CPU_p self) {
	return FIFO_dequeue(self->readyQueue);
}

void CPU_createdQueue_enqueue(CPU_p self, PCB_p pcb) {
	FIFO_enqueue(self->createdQueue, pcb);
}

PCB_p CPU_createdQueue_dequeue(CPU_p self) {
	return FIFO_dequeue(self->createdQueue);
}

void CPU_terminatedQueue_enqueue(CPU_p self, PCB_p pcb) {
	FIFO_enqueue(self->terminatedQueue, pcb);
}

PCB_p CPU_terminatedQueue_dequeue(CPU_p self) {
	return FIFO_dequeue(self->terminatedQueue);
}

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

	PCB_p testEnqueuePCB = PCB_constructorWithEmpty();
	CPU_readyQueue_enqueue(testCPU, testEnqueuePCB);
	PCB_p testDequeuePCB = CPU_readyQueue_dequeue(testCPU);
	printf("\nDequeue PCB Test: %s\n", PCB_toString(testDequeuePCB));



	exit(0);
}

