//
//  CPU.c
//  testC
//
//  Created by Khoa Doan on 1/23/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "CPU.h"
#include <unistd.h>

unsigned int PCB_ID = 0;
Timer_p myTimer;
IO_p myIO1;
IO_p myIO2;

CPU_p CPU_constructor(void) {
    srand((unsigned) time(NULL));
    CPU_p myCPU = malloc (sizeof(struct cpu_struct));
    myCPU->timer = 0;
    myCPU->pc = 0;
    myCPU->sysStack = Stack_constructor();
    myCPU->current = NULL;
    myCPU->createdQueue = FIFO_constructor();
    myCPU->readyQueue = FIFO_constructor();
    myCPU->terminateQueue = FIFO_constructor();
    return myCPU;
}

void CPU_destructor(CPU_p me) {
    PCB_destructor(me->current);
    Stack_destructor(me->sysStack);
    FIFO_destructor(me->readyQueue);
    FIFO_destructor(me->createdQueue);
    FIFO_destructor(me->terminateQueue);
    free(me);
}

void CPU_ISR(CPU_p me, enum interrupt_type itype) {
    PCB_setState(me->current, interrupted);
    PCB_setSW(me->current, Stack_pop(me->sysStack));
    PCB_setPC(me->current, Stack_pop(me->sysStack));
    CPU_scheduler(me, itype);
    CPU_IRET(me);
}

void CPU_IRET(CPU_p me) {
    Stack_pop(me->sysStack);
    me->pc = Stack_pop(me->sysStack);
}

void CPU_trapServiceHandler(CPU_p me, IO_p io) {
    PCB_setState(me->current, waiting);
    PCB_setPC(me->current, me->pc);
    FIFO_enqueue(io, me->current);
    CPU_scheduler(me, ...);
    CPU_IRET(me);
}

void CPU_scheduler(CPU_p me, enum interrupt_type itype) {
    printf("Saving current state of processor to PCB:\n%s", PCB_toString(me->cur));
    if (itype == timer) {
        PCB_setState(me->current, ready);
        FIFO_enqueue(me->readyQueue, me->current);
        CPU_dispatcher(me);
    }// else if (itype == io1) {
    //     PCB_setState(myIO1->current, ready);
    //     PCB_setState(me->current, ready);
    //     FIFO_enqueue(me->readyQueue, myIO1->current);
    // } else if (itype == io2) {
    //     PCB_setState(me->current, waiting);
    //     FIFO_enqueue(myIO2->waitingQueue, me->current);
    //     CPU_dispatcher(me);
    // }
    // do some additional housekeeping
}

void CPU_dispatcher(CPU_p me) {
    //TODO 1.) Save the state of the current process into its PCB (here we mean the PC value)
    me->current = FIFO_dequeue(me->readyQueue);
    PCB_setState(me->current, running);
    Stack_push(me->sysStack, PCB_getPC(me->current));
    Stack_push(me->sysStack, PCB_getSW(me->current));
    printf("Switching to: %s", PCB_toString(me->current));
    printf("Q: %s\n\n\n", FIFO_toString(me->readyQueue));
}

void createNewProcess(CPU_p me) {

    unsigned int random_number_0_to_5;
    random_number_0_to_5 = rand() % 6;
    printf("random number %d\n", random_number_0_to_5);
    for (int i = 1; i <= random_number_0_to_5; i++) {
        FIFO_enqueue(me->createdQueue, PCB_constructor(PCB_ID++, rand() / (RAND_MAX / 16), new, 0, 0));
    }
}

void mainLoop(CPU_p me) {

    while(1) {
        // create a new PCB between 0 to 5
        if(PCB_ID < 30) {
            createNewProcess(me);
        }

        // simulate CPU running
        //      1. move the pcb from created queue to ready queue.
        while (FIFO_size(me->createdQueue) != 0){
            PCB_p temp = FIFO_dequeue(me->createdQueue);
            PCB_setState(temp, ready);
            FIFO_enqueue(me->readyQueue, temp);
            printf("Process has been enqueued %sQ: %s\n\n", PCB_toString(temp), FIFO_toString(me->readyQueue));
        }
        //      2. dequeue the first pcb in the ready queue.
        if (me->current == NULL && FIFO_size(me->readyQueue) > 0) {
            me->current = FIFO_dequeue(me->readyQueue);
            me->pc = me->current->addressPC;
            PCB_setState(me->current, running);
        } else {
            break;
            // FIXME what if there is no PCB in ready queue, should I stop the while loop??
        }

        me->pc++;   //increment cpu pc

        /*****************************************/
        /********* Check Timer Interrupt *********/
        /*****************************************/
        if (Timer_update(myTimer)) {
            // Timer interrupt handler occurs
            Stack_push(me->sysStack, me->pc); // before it occurs
            Stack_push(me->sysStack, me->current->addressSW);
            CPU_ISR(me, timer);
        }

        /*****************************************/
        /**** Check I/O Completion Interrupts ****/
        /*****************************************/

        //TODO check if IO completion interrupt has cocured in if statement
        if (IO_updateAndCheckCompletion(IO1) || IO_updateAndCheckCompletion(IO2)) {
            Stack_push(me->sysStack, me->pc); // before it occurs
            Stack_push(me->sysStack, me->current->addressSW);
            if (IO_updateAndCheckCompletion(IO1)) {
                CPU_ISR(me, io1);
            } else {
                CPU_ISR(me, io2);
            }
        }

        /*****************************************/
        /******* Call trap service handler *******/
        /*****************************************/
        for (int i = 0; i < 4; i++) {
            if (me->pc == me->curent->io1_trap[i]) {
                Stack_push(me->sysStack, me->pc);
                Stack_push(me->sysStack, me->current->addressSW);
                // CPU_ISR(me, io1);
            }
            if (me->pc == me->curent->io2_trap[i]) {
                Stack_push(me->sysStack, me->pc);
                Stack_push(me->sysStack, me->current->addressSW);
                // CPU_ISR(me, io2);
            }
        }

        /*****************************************/
        /* Process termination check /
        /*****************************************/
        //see if pc is over MAX_PC
        if (me->pc >= me->current->max_pc) {
            me->pc = 0;
            PCB_incrementTermCount(me->current);
        }

        //if process has run full course, move to termination stack
        if (PCB_checkTerminate(me->current)) {
            PCB_terminate(me->current);
            //move process to termination queue
            FIFO_enqueue(me->terminatedQueue, me->current);
            me->current = NULL;
        }
    }
}

int main() {
    CPU_p cpu = CPU_constructor();
    myTimer = Timer_constructor();
    myIO1 = IO_constructor();
    myIO2 = IO_constructor();
    mainLoop(cpu, cpuTimer, IO1, IO2);
    CPU_destructor(cpu);
    return 0;
}
