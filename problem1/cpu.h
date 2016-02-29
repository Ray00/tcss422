/***************************************************************************
* cpu.h
*
* Programming Team:
* Ray Kim
* Kyle Doan
* Nabil Fadili
* Riley Gratzer
*
* Date: 2/12/16
*
****************************************************************************/

#ifndef CPU_H_
#define CPU_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "pcb.h"
#include "fifoqueue.h"
#include "timer.h"
#include "stack.h"
#include "IO_x.h"


#define MAX_PROC 30

typedef struct cpu_type {
    TIMER_STR_p timer;
    unsigned int pc;
    STACK_STR_p sysStack;
    PCB_p currentProcess;
    PCB_QUEUE_STR_p readyQueue;					//fifoqueue
    PCB_QUEUE_STR_p createdQueue;				//fifoqueue
    PCB_QUEUE_STR_p terminatedQueue;			//fifoqueue
} CPU;
typedef CPU * CPU_p;

/*** global extern variables ***/
extern int GLOBAL_TIMER_INTERRUPT;
extern int GLOBAL_IO_COMPLETION_INTERRUPT;
extern unsigned int GLOBAL_NEW_IO_PROC_ID;
extern PCB_p GLOBAL_IDLE_process;

/*** function pointer signature used for all handler functions ***/
//typedef void (*handler_fp)(PCB_P);


/*** Construction Prototypes ****/
void createNewProcesses(CPU_p);
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

void CPU_dispatcher(CPU_p);
//1.) Save the state of the current process into its PCB (here we mean the PC value)
//2.) Dequeue the next waiting process (PCB)
//3.) Change its state to running
//4.) Copy its PC value (and SW if you implement it) to the SysStack location to replace the PC of the interrupted process
//5.) Return

char* CPU_toString(CPU_p);

/*New for final assignment*/
void createNewIOProcesses(CPU_p);
void createNewIntensiveProcesses(CPU_p);
void createNewRealisticProcesses(CPU_p);

#endif /* CPU_H_ */
