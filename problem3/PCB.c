/*
 * pcb.c
 *
 *  Created on: Jan 7, 2016
 *      Author: Kyle Doan, nabilfadili
 */

#include "pcb.h"

/*
 * Function:  PCB_constructor
 * --------------------
 * Constructs a pcb object, returning a pointer to the pcb object
 * in the heap
 *
 *  params:  pID processID
 *			 priority
 *			 s
 *			 addPC
 *			 addSp
 *  returns: PCB_p pointer to the PCB object in the heap
 */
PCB_p PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSW, unsigned int addSp) {
    PCB_p result = (PCB_p) malloc(sizeof(PCB));
    if (result != (PCB_p) NULL) {
        srand((unsigned) time(NULL));
        time_t rawtime;
        time (&rawtime);

        result->process_num = pID;
        result->priority = priority;
        result->state = s;
        result->addressPC = addPC;
        result->addressSW = addSW;
        result->addressSpace = addSp;
        result->max_pc = MAX_PC;
        result->creation = localtime(&rawtime);
        result->termination = NULL;
        result->terminate = rand() / (RAND_MAX / 15) + 1;  // FIXME
        result->term_count = 0;
        result->io1_trap[0] = rand() / (RAND_MAX / 300);
        result->io2_trap[0] = rand() / (RAND_MAX / 300);
        unsigned int temp, i = 1;
        // FIXME it is possible that it will occur infinity loop.
        while (i < 4) {
            temp = rand() / (RAND_MAX / 2345);
            if (temp > result->io1_trap[i - 1]) {
                result->io1_trap[i] = temp;
                i++;
            }
        }
        i = 1;
        while (i < 4) {
            temp = rand() / (RAND_MAX / 2345);
            if (temp > result->io2_trap[i - 1]) {
                result->io2_trap[i] = temp;
                i++;
            }
        }
    }
    return result;
}

PCB_p PCB_constructorWithEmpty() {
	PCB_p result = (PCB_p) malloc(sizeof(PCB));
	result->priority = -1;
	return result;
}

/*
 * Function:  PCB_destructor
 * --------------------
 * Deallocates the memory being used by the passed PCB pointer.
 *
 *  params: PCB_p pointer to the PCB object in the heap
 */
void PCB_destructor(PCB_p p) {
	free(p);
}

/*
 * Function:  PCB_setProcessNumber
 * --------------------
 * Sets the passed PCB object's process_num field to the passed process number.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated process number.
 */
void PCB_setProcessNumber(PCB_p p, unsigned int process_num) {
	p->process_num = process_num;
}

unsigned int PCB_getProcessNumber(PCB_p p) {
	return p->process_num;
}

/*
 * Function:  PCB_setPriority
 * --------------------
 * Sets the passed PCB object's priority field to the passed priority.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated priority.
 */
void PCB_setPriority(PCB_p p, unsigned int priority) {
	p->priority = priority;
}

/*
 * Function:  PCB_getPriority
 * --------------------
 * Gets the passed PCB object's priority.
 *
 *  returns: The PCB object's priority.
 */
unsigned int PCB_getPriority(PCB_p p) {
	return p->priority;
}

/*
 * Function:  PCB_setPC
 * --------------------
 * Sets the passed PCB object's PC address field to the passed addressPC.
 *
 *  params: PCB_p pointer to the PCB object in the heap and the designated priority.
 */
void PCB_setPC (PCB_p self, unsigned int pc) {
    self->addressPC = pc;
}

/*
 * Function:  PCB_getPC
 * --------------------
 * Gets the passed PCB object's PC address.
 *
 *  returns: The PCB object's PC address.
 */
unsigned int PCB_getPC (PCB_p self) {
    return self->addressPC;
}

void PCB_setSW (PCB_p me, unsigned int sw) {
    me->addressSW = sw;
}

unsigned int PCB_getSW (PCB_p me) {
    return me->addressSW;
}

void PCB_setState (PCB_p self, enum state_type s) {
    self->state = s;
}

void PCB_incrementTermCount(PCB_p me) {
    me->term_count++;
}

/*
 * Function:  PCB_checkTerminate
 * --------------------
 * Checks if term count equals terminate field
 * If it does, process terminates
 * if terminate == 0, the process runs infinitely
 *
 * Created by Ray
 *
 * params:	PCB_p           this
 * return:  0               if process is infinite or should not termiante
 *          1               if process has terminated and needs to be removed
 */
unsigned int PCB_checkTerminate(PCB_p this) {
    return (this->terminate == this->term_count) ? 1 : 0;
}

void PCB_terminate(PCB_p this) {
    //Set termination time
    time_t rawtime;
    time (&rawtime);

    this->termination = localtime (&rawtime);
    this->state = terminated;
}

char* getStateString(enum state_type state) {
    switch (state) {
        case new: return "new";
        case waiting: return "waiting";
        case ready: return "ready";
        case running: return "running";
        case halted: return "halted";
        case interrupted: return "interrupted";
        case terminated: return "terminated";
    }
}

/*
 * Function:  PCB_toString
 * --------------------
 * Prints relevant information about the PCB object to the console for
 * testing/debugging purposes.
 *
 * params:	PCB_p pointer to the PCB object in the heap.
 */
 char* PCB_toString(PCB_p me) {
     char * result = (char *) malloc(sizeof(char) * 100);
     sprintf(result, "content: PCB_ID: %d, Priority: %d, State: %s, PC: 0x%04X, etc.\n",
             me->process_num, me->priority, getStateString(me->state), me->addressPC);
     return result;
 }

 char* PCB_printCreatedTime(PCB_p me) {
     char * result = (char *) malloc(sizeof(char) * 50);
     sprintf(result, "Process created: PID %d at %s", me->process_num,
                            asctime(me->creation));
     return result;
 }

 char* PCB_printTerminatedTime(PCB_p me) {
     char * result = (char *) malloc(sizeof(char) * 50);
     if (me->termination != NULL) {
         sprintf(result, "Process created: PID %d at %s", me->process_num,
                                asctime(me->termination));
     } else {
         sprintf(result, "Process hasn't terminated yet.");
     }     
     return result;
 }
