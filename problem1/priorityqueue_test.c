//
//  priorityqueue_test.c
//  422 Problem 1
//
//  Created by Riley Gratzer on 1/12/16.
//  Copyright © 2016 Riley Gratzer. All rights reserved.
//

#include <stdio.h>
#include "priorityqueue.h"

int main(int argc, const char * argv[]) {
    
    PriorityQueue_p testing = PriorityQueue_constructor();
    PCB_p process1 = PCB_constructor(1, 2, ready, 0, 0);
    PCB_p process2 = PCB_constructor(2, 3, ready, 0, 0);
    PCB_p process3 = PCB_constructor(3, 1, ready, 0, 0);
    PCB_p process4 = PCB_constructor(4, 0, ready, 0, 0);
    PCB_p process5 = PCB_constructor(5, 0, ready, 0, 0);
    PCB_p process6 = PCB_constructor(6, 13, ready, 0, 0);
    PCB_p process7 = PCB_constructor(7, 0, ready, 0, 0);
    PCB_p process8 = PCB_constructor(8, 11, ready, 0, 0);
    PCB_p process9 = PCB_constructor(9, 11, ready, 0, 0);
    priority_enqueue(testing, process1);
    priority_enqueue(testing, process2);
    priority_enqueue(testing, process3);
    priority_enqueue(testing, process4);
    priority_enqueue(testing, process5);
    priority_enqueue(testing, process6);
    priority_enqueue(testing, process7);
    priority_enqueue(testing, process8);
    priority_enqueue(testing, process9);
    
    printf("Visulization of Processes in Ready Queue:\n");
    printf("%s", PriorityQueue_toString(testing));
    
    printf("\nRemoving Processes from Ready Queue by priority...\n");
    
    PCB_p retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));
    retrieval = priority_dequeue(testing);
    printf("%s", PCB_toString(retrieval));

    PriorityQueue_destructor(testing);
    
    return 0;
}
