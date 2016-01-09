//
//  pcb.h
//
//  Created by Khoa Doan on 1/8/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#ifndef PCB_H
#define PCB_H

#include <stdlib.h>
#include <stdio.h>

enum state_type {new, ready, running, waiting, halted};

typedef struct pcb {
	int process_num;
	int priority_num;
    enum state_type state;
    int addressPC;
    int addressSpace;

} PCB;

typedef PCB * PCB_p;

PCB_p pcbConstructor(int, int, enum state_type, int, int);
void pcbDestructor(PCB_p);

char * pcb_toString(PCB_p);
#endif 
