//
//  CPU.h
//  testC
//
//  Created by Khoa Doan on 1/23/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#ifndef CPU_h
#define CPU_h

#include "fifoqueue.h"
#include "timer.h"
#include "stack.h"
#include "IO.h"
#include <stdio.h>

#define TIME_SLICE 10

typedef struct cpu_struct {
    unsigned int timer;
    unsigned int pc;
    Stack_p sysStack;
    PCB_p current;
    PCB_QUEUE_STR_p readyQueue;
    PCB_QUEUE_STR_p createdQueue;
    PCB_QUEUE_STR_p terminateQueue;
} *CPU_p;

enum interrupt_type {timer, io1, io2};

CPU_p CPU_constructor(void);
void CPU_destructor(CPU_p);
void CPU_ISR(CPU_p, enum interrupt_type);
void CPU_IRET(CPU_p);
void CPU_scheduler(CPU_p, enum interrupt_type);
void CPU_dispatcher(CPU_p);
void mainLoop(CPU_p);

#endif /* CPU_h */
