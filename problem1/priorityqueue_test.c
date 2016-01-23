//
//  priorityqueue_test.c
//  422 Problem 1
//
//  Created by Riley Gratzer on 1/12/16. Modified by Ray Kim on 1/13/16
//  Copyright © 2016 Riley Gratzer. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "priorityqueue.h"

//int main(int argc, const char * argv[]) {
//    srand((unsigned) time(NULL));
//    unsigned int random_num_range_4_to_6;
//    unsigned int pcbs_remain = 1;
//    
//    PriorityQueue_p priority_queue = PriorityQueue_constructor();
//    
//    char * dequeued_pcbs = (char *) malloc(sizeof(char) * 1000);
//    printf("Visualization of Processes in Ready Queue:\n");
//    
//    
//    int i;
//    int j;
//    int k;
//    for (i = 0; i < 10; i++) {
//        //generate pcbs with random priorities and enqueue them into priority_queue
//        for (j = 0; j < 10; j++) {
//            //creating and populating the new pcbs
////            PCB_p temp_pcb = (PCB_p) malloc(sizeof(PCB));
////            PCB_p temp_pcb = PCB_constructor((i*10 + j), rand() / (RAND_MAX / 16), 0, 0, 0);
//            
//            //enqueue pcbs
//            priority_enqueue(priority_queue, PCB_constructor((i*10 + j), rand() / (RAND_MAX / 16), 0, 0, 0));
//
//        }
//        
//        //generate random between 4 and 6
//        random_num_range_4_to_6 = (rand() / (RAND_MAX / 2)) + 4;
//
//        //dequeue 4-6 items
//        for (k = 0; k < random_num_range_4_to_6; k++) {
//            PCB_p dequeued_pcb_p = priority_dequeue(priority_queue);
//            strcat(dequeued_pcbs, "Removed ");
//            strcat(dequeued_pcbs, PCB_toString(dequeued_pcb_p));
//        }
//        strcat(dequeued_pcbs, "\n\n");
//        
//        //print the state of the priority queue
//        printf("%s", PriorityQueue_toString(priority_queue));
//        
//        //print dequeued pcbs
//        puts(dequeued_pcbs);
//        
//        dequeued_pcbs[0] = '\0'; //clear out char * that holds dequeued pcbs
//        
//        //sleep for 10 seconds
//        sleep(1);
//    }
//    
//    //empty out the remaining pcbs
//    while (pcbs_remain) {
//        //set next random number of pcbs to dequeue
//        random_num_range_4_to_6 = (rand() / (RAND_MAX / 2)) + 4;
//        
//        for (k = 0; k < random_num_range_4_to_6; k++) {
//            PCB_p dequeued_pcb_p = priority_dequeue(priority_queue);
//            
//            //upon receiving NULL PCB pointer, break
//            if (dequeued_pcb_p == NULL) {
//                pcbs_remain = 0;
//                break;
//            }
//            strcat(dequeued_pcbs, "Removed ");
//            strcat(dequeued_pcbs, PCB_toString(dequeued_pcb_p));
//        }
//        strcat(dequeued_pcbs, "\n\n");
//        //print dequeued pcbs
//        puts(dequeued_pcbs);
//        
//        dequeued_pcbs[0] = '\0'; //clear out char * that holds dequeued pcbs
//        
//        //sleep for 10 seconds
//        sleep(1);
//    }
//
//
//    PriorityQueue_destructor(priority_queue);
//    
//    return 0;
//}
