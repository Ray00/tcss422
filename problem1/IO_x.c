/***************************************************************************
* IO_x.c
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

#include "IO_x.h"

IO_STR_p IO_constructor() {
    IO_STR_p this = (IO_STR_p) malloc(sizeof(IO_STR));
    this->elapsed_cycles = 0;
    this->waitingQueue = FIFO_constructor();
    return this;
}

void IO_destructor(IO_STR_p this) {
    FIFO_destructor(this->waitingQueue);
    free(this);
}

void IO_addProcess(IO_STR_p this, PCB_p pcb) {
    FIFO_enqueue(this->waitingQueue, pcb);
}

unsigned int IO_updateCheckCompletion(IO_STR_p this) {
    if (FIFO_size(this->waitingQueue) > 0) {
//        printf("IO blocked cycles: %d\n", this->elapsed_cycles);
        if (this->elapsed_cycles < IO_BLOCK_CYCLES) {
            this->elapsed_cycles++;
            return 0;
        } else {
            return 1;
        }
    }

    return 0;
}

PCB_p IO_dequeue_waitQueue(IO_STR_p this) {
    this->elapsed_cycles = 0;
    return FIFO_dequeue(this->waitingQueue);
}
