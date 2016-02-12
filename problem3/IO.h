//
//  IO.h
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#ifndef IO_H_
#define IO_H_

#include <time.h>
#include <stdlib.h>
#include "PCB.h"
#include "fifoqueue.h"

typedef struct IO_struct {
    unsigned int count;
    PCB_p current;
    PCB_QUEUE_STR_p waitingQueue;
} *IO_p;

IO_p IO_constructor(void);
void IO_destructor(IO_p);
void IO_addProcess(IO_p, PCB_p);
unsigned int IO_updateAndCheckCompletion(IO_p);

#endif
