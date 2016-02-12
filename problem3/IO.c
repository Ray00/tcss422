//
//  IO.c
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "IO.h"

IO_p IO_constructor(void) {
    IO_p me = malloc(sizeof(struct IO_struct));
    me->count = 0;
    me->current = NULL;
    me->waitingQueue = FIFO_constructor();
    return me;
}

void IO_destructor(IO_p me) {
    FIFO_destructor(me->waitingQueue);
    free(me);
}

void IO_addProcess(IO_p me, PCB_p pcb) {
    FIFO_enqueue(me->waitingQueue, pcb);
}

unsigned int IO_updateAndCheckCompletion(IO_p me) {
    if (me->current == NULL && FIFO_size(me->waitingQueue) > 0) {
        srand((unsigned) time(NULL));
        me->current = FIFO_dequeue(me->waitingQueue);
        //the random number must be 3 - 5 times timer countdown
        me->count = (rand() / (RAND_MAX / 601)) + 900;
    }
    me->count--;
    if (me->count == 0) {
        return 1;
    } else {
        return 0;
    }
}
