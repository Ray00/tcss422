//
//  fifoqueue_test.c
//
//  Created by Khoa Doan on 1/7/16. Modified by Ray Kim on 1/13/16
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
int main() {
    printf("FIFO Queue Test\n");
    srand((unsigned) time(NULL));
    
    //Create a queue object
    PCB_QUEUE_STR_p fifoQueue = (PCB_QUEUE_STR_p) malloc(sizeof(PCB_QUEUE_STR));
    fifoQueue = FIFO_constructor();
    
    unsigned int i;
    unsigned int random_num_within_20 = rand() / (RAND_MAX / 20);
    unsigned int random_within_range = random_num_within_20 + 10; //between 10-30
    
    PCB_QUEUE_STR_p fifo_queue = FIFO_constructor();
    
    //creation of a random number of PCBs (between 10 and 30)
    for (i = 0; i < random_within_range; i++) {
        //creating and populating the new pcbs
        PCB_p temp_pcb = (PCB_p) malloc(sizeof(PCB));
        temp_pcb = PCB_constructor(i, rand() / (RAND_MAX / 16), 0, 0, 0);

        //create node
        FIFO_enqueue(fifo_queue, temp_pcb);
        
        //print out a representation of the queue as it grows
        //pcb linked list
        printf("%s :", FIFO_toString(fifo_queue));
        
        //added pcb
        puts(PCB_toString(temp_pcb));
    }
    
    //dequeueing
    while (fifo_queue->num_nodes > 0) {
        PCB_p dequeued_pcb = FIFO_dequeue(fifo_queue);
        
        //print out the queue with each dequeue
        printf("%s\n", FIFO_toString(fifo_queue));
        
        //print the contents of the pcb object just dequeued
        puts(PCB_toString(dequeued_pcb));
    }

    // TODO print the contents of the last pcb enqueued.
//    puts(FIFO_toString(fifoQueue));
//    FIFO_enqueue(fifoQueue, process1);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process1));
//    FIFO_enqueue(fifoQueue, process2);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process2));
//    FIFO_enqueue(fifoQueue, process3);
//    printf("%s : %s", FIFO_toString(fifoQueue), PCB_toString(process3));

    exit(0);
}
