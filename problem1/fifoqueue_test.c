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
//    PCB_p process1 = (PCB_p) malloc(sizeof(PCB));
//    PCB_p process2 = (PCB_p) malloc(sizeof(PCB));
//    PCB_p process3 = (PCB_p) malloc(sizeof(PCB));
//
//    process1 = pcbConstructor(1, 0);
//    process2 = pcbConstructor(2, 12);
//    process3 = pcbConstructor(3, 20);
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
