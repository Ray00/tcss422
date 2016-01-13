//
//  fifoqueue_test.c
//
//  Created by Khoa Doan on 1/7/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "fifoqueue.h"
#include <time.h>

/*********************************************************************
 * Function:  test Main()
 * --------------------
 * test driver
 *
 *
 *  params: 	PCB_QUEUE_STR_p this
 *  returns:	NODE_STR_p head node that will be taken off the queue
 *********************************************************************/
//int main() {
//    printf("FIFO Queue Test\n");
//    srand((unsigned) time(NULL));
//    PCB_p process1 = (PCB_p) malloc(sizeof(PCB));
//    PCB_p process2 = (PCB_p) malloc(sizeof(PCB));
//    PCB_p process3 = (PCB_p) malloc(sizeof(PCB));
//    process1 = PCB_constructor(rand() / (RAND_MAX / 31), rand() / (RAND_MAX / 16), 0, 0, 0);
//    process2 = PCB_constructor(rand() / (RAND_MAX / 31), rand() / (RAND_MAX / 16), 1, 10, 5);
//    process3 = PCB_constructor(rand() / (RAND_MAX / 31), rand() / (RAND_MAX / 16), 1, 255, 10);
//
//    PCB_QUEUE_STR_p fifoQueue = (PCB_QUEUE_STR_p) malloc(sizeof(PCB_QUEUE_STR));
//    fifoQueue = FIFO_constructor();
//
//    // TODO print the contents of the last pcb enqueued.
//    puts(FIFO_toString(fifoQueue));
//    FIFO_enqueue(fifoQueue, process1);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process1));
//    FIFO_enqueue(fifoQueue, process2);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process2));
//    FIFO_enqueue(fifoQueue, process3);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process3));
//
//    exit(0);
//}
