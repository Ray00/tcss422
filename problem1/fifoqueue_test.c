/***************************************************************************
* fifoqueue_test.c
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

//int main(int argc, const char * argv[]) {
//    printf("---FIFO Queue Test---\n");
//    srand((unsigned) time(NULL));
//
//    //Create a queue object
//    PCB_QUEUE_STR_p fifoQueue = (PCB_QUEUE_STR_p) malloc(sizeof(PCB_QUEUE_STR));
//    fifoQueue = FIFO_constructor();
//
//    unsigned int i;
//    unsigned int random_num_within_20 = rand() % 20;
//    unsigned int random_within_range = random_num_within_20 + 10; //between 10-30
//
//    PCB_QUEUE_STR_p fifo_queue = FIFO_constructor();
//
//    //creation of a random number of PCBs (between 10 and 30)
//    for (i = 0; i < random_within_range; i++) {
//        //creating and populating the new pcbs
//        PCB_p temp_pcb = (PCB_p) malloc(sizeof(PCB));
//        temp_pcb = PCB_constructor(i, rand() / (RAND_MAX / 16), 0, 0, 0);
//
//        //enqueue into fifo queue
//        FIFO_enqueue(fifo_queue, temp_pcb);
//
//        //print out a representation of the queue as it grows
//        //pcb linked list
//        printf("Q: %s :", FIFO_toString(fifo_queue));
//
//        //added pcb
//        puts(PCB_toString(temp_pcb));
//    }
//
//    //dequeueing
//    while (fifo_queue->num_nodes > 0) {
//        PCB_p dequeued_pcb = FIFO_dequeue(fifo_queue);
//
//        //print out the queue with each dequeue
//        printf("Q: %s\n", FIFO_toString(fifo_queue));
//
//        //print the contents of the pcb object just dequeued
//        puts(PCB_toString(dequeued_pcb));
//    }
//
//    //destroy fifo_queue
//    FIFO_destructor(fifo_queue);
//
//    exit(0);
//}
