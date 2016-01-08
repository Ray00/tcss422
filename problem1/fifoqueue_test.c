//
//  fifoqueue_test.c
//  testC
//
//  Created by Khoa Doan on 1/7/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include <stdio.h>
#include "fifoqueue.h"


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
//    PCB_p process1 = PCB_constructor();
//    PCB_p process2 = PCB_constructor();
//    PCB_p process3 = PCB_constructor();
//    int process_num;
//    int priority;
//
//    process_num = 1;
//    priority = 0;
//    PCB_setProcessNumber(process1, process_num);
//    PCB_setPriority(process1, priority);
//
//    process_num = 2;
//    priority = 5;
//    PCB_setProcessNumber(process2, process_num);
//    PCB_setPriority(process2, priority);
//
//    process_num = 3;
//    priority = 10;
//    PCB_setProcessNumber(process3, process_num);
//    PCB_setPriority(process3, priority);
//
//    NODE_STR_p node1 = (NODE_STR_p) malloc(sizeof(NODE_STR));
//    NODE_STR_p node2 = (NODE_STR_p) malloc(sizeof(NODE_STR));
//    NODE_STR_p node3 = (NODE_STR_p) malloc(sizeof(NODE_STR));
//
//    node1 = nodeConstructor(process1);
//    node2 = nodeConstructor(process2);
//    node3 = nodeConstructor(process3);
//
//    PCB_QUEUE_STR_p fifoQueue = (PCB_QUEUE_STR_p) malloc(sizeof(PCB_QUEUE_STR));
//    fifoQueue = queueConstructor();
//
//    // TODO print the contents of the last pcb enqueued.
//    puts(toString(fifoQueue));
//    enqueue(fifoQueue, node1);
//    puts(toString(fifoQueue));
//    enqueue(fifoQueue, node2);
//    puts(toString(fifoQueue));
//    enqueue(fifoQueue, node3);
//    puts(toString(fifoQueue));
//
//    exit(0);
//}
