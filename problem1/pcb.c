//
//  pcb.c
//
//  Created by Khoa Doan on 1/7/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "pcb.h"

/*
 * Function:  pcbConstructor
 * --------------------
 * constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  params:     pID processID
 *              priority priority level of the process. Lower number, higher priority.
 *  returns: 	PCB_p pointer to the PCB object in the heap
 */

PCB_p pcbConstructor(int pID, int priority) {
    PCB_p result = (PCB_p) malloc(sizeof(PCB));
    if (result != (PCB_p) NULL) {
        result->process_num = pID;
        result->priority_num = priority;
    }
    return result;
}

/*
 * Function:  queueDestructor
 * --------------------
 * releases resources of PCB object
 *
 *  params: 	PCB_QUEUE_STR_p me
 */
void pcbDestructor(PCB_p me) {
    free(me);
}