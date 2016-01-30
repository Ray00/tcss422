/*
 * cpu.c
 *
 *  Created on: Jan 22, 2016
 *      Author: nabilfadili, raykim
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "cpu.h"

#define MAX_PROC 30
#define TIME_SLICE 10   // suppose TIME_SLICE is 10 ns

unsigned int G_NEW_PROC_ID = 0;
unsigned int G_LOOP_ITER_NUM = 0;
PCB_p IDLE; 
FILE *fp;

/*
 * Function:  Main
 * --------------------
 *
 */

void createNewProcesses(CPU_p self) {
    int random_num_range_0_to_5 = rand() % 6; //create a random number of new processes, between 0 and 5

    //place random num processes into cpu_p->createdQueue
    for (int i = 1; i <= random_num_range_0_to_5; i++) {

        G_NEW_PROC_ID += 1;

        //PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSp)
        FIFO_enqueue(self->createdQueue, PCB_constructor(G_NEW_PROC_ID, 1, new, 0, 0));
    }
}

void mainLoop(CPU_p self) {

	/*File I/O*/
	fp = fopen("scheduleTrace.txt", "w+");

    /* set idle */
    self->currentProcess = IDLE;
    self->pc = 0;

    /* round robin simulation */
    while (G_NEW_PROC_ID < MAX_PROC) {
        self->timer = 0;

        //create up to 5 new processes
        createNewProcesses(self);

        //add first in line process of self->createdQueue (if exists) to self->readyQueue
        // FIXME (Kyle) why just add one process?? I move all the process from createdQueue to readyQueue
        // If there is any question, let me know.
        while (FIFO_size(self->createdQueue) != 0) {
            PCB_p temp_pcb_p = FIFO_dequeue(self->createdQueue);
            PCB_setState(temp_pcb_p, ready);
            FIFO_enqueue(self->readyQueue, temp_pcb_p);

            printf("Process ID: %u Enqueued\n", temp_pcb_p->process_num); //print message that process has been enqueued
            fprintf(fp, "Process ID: %u Enqueued\n", temp_pcb_p->process_num); //output to file

            puts(PCB_toString(temp_pcb_p)); //print PCB contents
            fprintf(fp, "%s", PCB_toString(temp_pcb_p)); //output PCB contents
            fprintf(fp, "\n");
        }
        
        //      2. dequeue the first pcb in the ready queue.
        if (self->currentProcess == IDLE && FIFO_size(self->readyQueue) > 0) {
            self->currentProcess = FIFO_dequeue(self->readyQueue);
            PCB_setState(self->currentProcess, running);
        }

        //increment the PC value by a random number between 3,000 and 4,000
        if (self->pc < 3000) {
            self->pc = rand() / (RAND_MAX / 1000) + 2000;
        }
        while (self->timer < TIME_SLICE) {
            self->timer++;
            self->pc += (rand() / (RAND_MAX / 1000)) + 3000;
            // if the process need io request, it up-calls here.
        }

        //pseudo-push PC to the system stack (interrupt does this in reality)
        CPU_SysStack_push(self, self->pc);

        /*****************************************/
        /********** Kernel Mode Starts ***********/
        /*****************************************/

        //call timer interrupt handler
        CPU_timerInterruptHandler(self, timer);

        /*****************************************/
        /*********** Kernel Mode Ends ************/
        /*****************************************/

        G_LOOP_ITER_NUM += 1; //increment loopIterationNum

        //sleep for timerQuantum amount of time
        //sleep(timerQuantum);
    }
}


CPU_p CPU_constructor(void) {
    srand((unsigned) time(NULL));
    CPU_p newCPU = (CPU_p) malloc(sizeof(CPU));
    IDLE = PCB_constructor(G_NEW_PROC_ID, 999, idle, 0, 0);
    newCPU->timer = 0;
    newCPU->pc = 0;
    newCPU->sysStack = 0;
    newCPU->currentProcess = NULL;
    /* queue instantiation */
    newCPU->readyQueue = FIFO_constructor();
    newCPU->createdQueue = FIFO_constructor(); //newly launched processes queue
    newCPU->terminatedQueue = FIFO_constructor(); //"for deallocation" queue

    return newCPU;
}

void CPU_destructor(CPU_p self) {
    FIFO_destructor(self->readyQueue);
    FIFO_destructor(self->createdQueue);
    FIFO_destructor(self->terminatedQueue);
    PCB_destructor(self->currentProcess);
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

void CPU_timerInterruptHandler(CPU_p self, enum interrupt_type itype) {
    //1.) Change the state of the running process to interrupted,
    PCB_setState(self->currentProcess, interrupted); 
    //2.) Save the CPU state to the PCB for that process (PC value)
    PCB_setPC(self->currentProcess, self->pc);
    //3.) Upcall to scheduler
    CPU_scheduler(self, itype);
    //4.) Put PC value from sysStack into pc
    self->pc = CPU_SysStack_pop(self); /********* IRET *********/

    //5.) Return
    return;
}

void CPU_scheduler(CPU_p self, enum interrupt_type interrupt) {
    switch(interrupt) {
        case timer:
            //1.) Change its state from interrupted to ready
            self->currentProcess->state = ready;
            //2.) Put the process back into the ready queue (if not idle process)
            if (self->currentProcess->state != idle) {
                FIFO_enqueue(self->readyQueue, self->currentProcess);
            }

            //3.) Upcall to dispatcher
            CPU_dispatcher(self);
            //4.) Additional house keeping
            //future TODO
            break;
        case io: break; /// not for this homework.
        default:
            printf("Interrupt type unspecified.");
    }
    //4.) Return - Chance to do more before returning but nothing yet
    return;
}

void CPU_dispatcher(CPU_p self) {
    PCB_p next_process_p = FIFO_dequeue(self->readyQueue);
    PCB_p last_process_p = self->currentProcess;

    //1.) Save the state of the current process into its PCB (here we mean the PC value)
    /*NOT SURE WHY WE NEED TO DO THIS AGAIN?*/

    //every fourth context switch
    if (G_LOOP_ITER_NUM % 4 == 0) {
        printf("Interrupted Process: %s", PCB_toString(last_process_p)); //print the contents of the running process
        printf("Switching to: %s\n", PCB_toString(next_process_p)); //print contents of the ready queue head PCB

        fprintf(fp, "Interrupted Process: %s", PCB_toString(last_process_p)); //output contents of running process
        fprintf(fp, "Switching to: %s\n", PCB_toString(next_process_p)); //output contents of ready queue head
    }

    //2.) Dequeue the next waiting process (PCB)
    self->currentProcess = next_process_p;
    //3.) Change its state to running
    PCB_setState(self->currentProcess, running);
    //4.) Copy its PC value (and SW if you implement it) to the SysStack location to replace the PC of the interrupted process
    CPU_SysStack_push(self, PCB_getPC(self->currentProcess));

    //after context switch
    if (G_LOOP_ITER_NUM % 4 == 0) {
        printf("Last Process: %s", PCB_toString(last_process_p)); //print the contents of the last process
        printf("Current Process: %s", PCB_toString(next_process_p)); //print contents of current process
        printf("Ready Queue: %s\n\n", FIFO_toString(self->readyQueue));

        fprintf(fp, "Last Process: %s", PCB_toString(last_process_p)); //print the contents of the last process
        fprintf(fp, "Current Process: %s", PCB_toString(next_process_p)); //print contents of current process
        fprintf(fp, "Ready Queue: %s\n\n", FIFO_toString(self->readyQueue));
    }

    //5.) Return
    return;
}

int main() {
   CPU_p cpu = CPU_constructor();
//    printf(CPU_toString(cpu));

//    unsigned int testPC = 3000;
//    CPU_setPC(cpu, testPC);
//    printf("\nsetPC Test: %u", CPU_getPC(cpu));

//    PCB_p testEnqueuePCB = PCB_constructorWithEmpty();
//    CPU_readyQueue_enqueue(cpu, testEnqueuePCB);
//    PCB_p testDequeuePCB = CPU_readyQueue_dequeue(cpu);
//    printf("\nDequeue PCB Test: %s\n", PCB_toString(testDequeuePCB));
    mainLoop(cpu);
    CPU_destructor(cpu);
    exit(0);
}