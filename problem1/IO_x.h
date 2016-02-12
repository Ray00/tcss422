/***************************************************************************
* IO_x.h
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

#ifndef IO_x_H_
#define IO_x_H_

#define IO_BLOCK_CYCLES 2000

#include <stdlib.h>
#include <stdio.h>
#include "fifoqueue.h"

typedef struct IO_struct {
    unsigned int elapsed_cycles;
    PCB_QUEUE_STR_p waitingQueue;
} IO_STR;
typedef IO_STR * IO_STR_p;

IO_STR_p IO_constructor(void);
void IO_destructor(IO_STR_p);
void IO_addProcess(IO_STR_p, PCB_p);
unsigned int IO_updateCheckCompletion(IO_STR_p);
PCB_p IO_dequeue_waitQueue(IO_STR_p);

#endif
