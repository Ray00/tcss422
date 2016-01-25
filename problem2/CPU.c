//
//  CPU.c
//  testC
//
//  Created by Khoa Doan on 1/23/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "CPU.h"
#include <time.h>
#include <unistd.h>

CPU_p CPU_constructor(void) {
    srand((unsigned) time(NULL));
    CPU_p myCPU = malloc (sizeof(struct cpu_struct));
    myCPU->timer = 0;
    myCPU->pc = 0;
    myCPU->sysStack = 0;
    myCPU->cur = NULL;
    myCPU->createdQueue = FIFO_constructor();
    myCPU->readyQueue = FIFO_constructor();
    myCPU->terminateQueue = FIFO_constructor();
    return myCPU;
}

void CPU_destructor(CPU_p self) {
    PCB_destructor(self->cur);
    FIFO_destructor(self->readyQueue);
    FIFO_destructor(self->createdQueue);
    FIFO_destructor(self->terminateQueue);
    free(self);
}

void CPU_ISR(CPU_p self, enum interrupt_type itype) {
    PCB_setState(self->cur, interrupted);
    PCB_setPC(self->cur, self->pc); 
    CPU_scheduler(self, itype);
    CPU_IRET(self);
}

void CPU_IRET(CPU_p self) {
    self->pc = self->sysStack;
}

void CPU_scheduler(CPU_p self, enum interrupt_type itype) {
    if (itype == timer) {
        printf("Saving current state of processor to PCB:\n%s", PCB_toString(self->cur));
        PCB_setState(self->cur, ready);
        FIFO_enqueue(self->readyQueue, self->cur);
        CPU_dispatcher(self);
    } else if (itype == io) {
        // put to io_queue
    }
    // do some additional housekeeping
}

void CPU_dispatcher(CPU_p self) {
    //TODO 1.) Save the state of the current process into its PCB (here we mean the PC value)
    self->cur = FIFO_dequeue(self->readyQueue);
    PCB_setState(self->cur, running);
    self->sysStack = PCB_getPC(self->cur);
    printf("Switching to: %s", PCB_toString(self->cur));
    printf("Q: %s\n\n\n", FIFO_toString(self->readyQueue));
}

void mainLoop(CPU_p self) {
    srand((unsigned) time(NULL));
    unsigned int random_number_0_to_5;
    unsigned int pcbID = 1;

    while(pcbID < 30) {
        // set a timer
        self->timer = 0;

        // create a new PCB between 0 to 5
        random_number_0_to_5 = rand() % 6;
        printf("random number %d\n", random_number_0_to_5);
        for (int i = 1; i <= random_number_0_to_5; i++) {
            FIFO_enqueue(self->createdQueue, PCB_constructor(pcbID++, rand() / (RAND_MAX / 16), new, 0, 0));
        }

        // simulate CPU running
        //      1. move the pcb from created queue to ready queue.
        for (int i = 1; i <= random_number_0_to_5; i++) {
            PCB_p temp = FIFO_dequeue(self->createdQueue);
            PCB_setState(temp, ready);
            FIFO_enqueue(self->readyQueue, temp);
            printf("Process has been enqueued %sQ: %s\n\n", PCB_toString(temp), FIFO_toString(self->readyQueue));
        }
        //      2. dequeue the first pcb in the ready queue.
        if (self->cur == NULL && FIFO_size(self->readyQueue) > 0) {
            self->cur = FIFO_dequeue(self->readyQueue);
            PCB_setState(self->cur, running);
        }
        //      3. Run the current pcb in the period of the time
        if (self->pc < 3000) {
            self->pc = rand() / (RAND_MAX / 1000) + 2000;
        }
        while (self->timer < TIME_SLICE) {
            self->timer++;
            self->pc++;
            // if the process need io request, it up-calls here.
        }
        // Timer interrupt handler occurs
        self->sysStack = self->pc; // before it occurs
        CPU_ISR(self, timer);

        sleep(1);
    }
}

int main() {
    CPU_p cpu = CPU_constructor();
    mainLoop(cpu);
    CPU_destructor(cpu);
    return 0;
}






























