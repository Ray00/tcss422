/*
 * pcb.c
 *
 *  Created on: Jan 7, 2016
 *      Author: Kyle Doan, nabilfadili
 */



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
        result->process_num = pID;
        result->priority = priority;
        result->state = s;
        result->addressPC = addPC;
        result->addressSW = addSW;
        result->addressSpace = addSp;
        result->max_pc = MAX_PC;
        result->terminate = 0;
        result->term_count = 0;

        //Get the creation time
        time_t rawtime;
        struct tm * timeinfo;
        time ( &rawtime );
        timeinfo = localtime ( &rawtime );

        result->creation = timeinfo;

        int i = 0;
        int j = 0;
        int temp = 0;
        int check = 0;
        srand(time(NULL));

        //Create I/O 1 Traps
        unsigned int * traps1 = (unsigned int *) malloc(sizeof(unsigned int) * MAX_CALLS_FOR_IO);
        result->io_1_array_ptr = traps1;

        temp = rand() % MAX_PC;
        traps1[0] = temp;
        //printf("%d\n", temp);
        for (i = 1; i < 4; i++) {
          temp = rand() % MAX_PC;
          //printf("%d\n", temp);
            check = 0;
          for (j = 0; j < i; j++) {
            if (temp == traps1[j]) {
              check = 1;
            }
          }
          if (check == 0) {
            traps1[i] = temp;
          } else {
            i--;
          }
        }
        //Sort Traps1
        i = 0;
        j = 0;
        temp = 0;
        for (i = 0; i < 4; i++) {
          for (j = i + 1; j < 4; j++) {
            if (traps1[i] > traps1[j]) {
                  temp =  traps1[i];
                  traps1[i] = traps1[j];
                  traps1[j] = temp;
            }
          }
        }

        result->io_1_traps = traps1;


        //Create I/O 2 Traps
        unsigned int * traps2 = (unsigned int *) malloc(sizeof(unsigned int) * MAX_CALLS_FOR_IO);
        result->io_2_array_ptr = traps2;

        temp = rand() % MAX_PC;
        traps2[0] = temp;
        for (i = 1; i < 4; i++) {
          temp = rand() % MAX_PC;
          check = 0;
          for (j = 0; j < i; j++) {
            if (temp == traps2[j]) {
              check = 1;
            }
          }
          if (check == 0) {
            traps2[i] = temp;
          } else {
            i--;
          }
        }
        //Sort Traps2
        i = 0;
        j = 0;
        temp = 0;
        for (i = 0; i < 4; i++) {
          for (j = i + 1; j < 4; j++) {
            if (traps2[i] > traps2[j]) {
                  temp =  traps2[i];
                  traps2[i] = traps2[j];
                  traps2[j] = temp;
            }
          }
        }
        result->io_2_traps = traps2;
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

int PCB_getProcessNumber(PCB_p p) {
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
int PCB_getPriority(PCB_p p) {
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
int PCB_getPC (PCB_p self) {
    return self->addressPC;
}

void PCB_setState (PCB_p self, enum state_type s) {
    self->state = s;
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
    if (this->term_count == 0) {
        return 0;
    } else if (this->terminate == this->term_count) {
        return 1
    }

    return 0;
}


void PCB_terminate(PCB_p this) {
    this->terminate = 1;

    //Set termination time
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    this->termination = timeinfo;
    this->state = terminated;
}


void PCB_incrementTermCount(PCB_p this) {
  this->term_count++;
}




/*
 * Function:  PCB_currPCHasIOCall
 * --------------------
 * Looks through IO device array of PCs to see if any device makes an IO request for current PC
 * Note: no two devices should make device calls during the same PC instruction
 *
 * Created by Ray
 *
 * params:	PCB_p           this
 *          unsigned int    current PC
 * return:  0               for no IO call
 *          1               if PC instruction makes call for device 1
 *          2               if PC instruction makes call for device 2
 */
unsigned int PCB_currPCHasIOCall (PCB_p this, unsigned int pc) {
    //check if PC matches either values pointed to by device array pointers
    if (pc == *(this->io_1_array_ptr) && (this->io_1_array_ptr < this->io_1_traps + MAX_CALLS_FOR_IO)) { //bounds checking to stay within io_1_traps
        (this->io_1_array_ptr)++; //increment pointer to next value
        return 1;
    } else if (pc == *(this->io_2_array_ptr) && (this->io_2_array_ptr < this->io_2_traps + MAX_CALLS_FOR_IO)) { //bounds checking to stay within io_2_traps
        (this->io_2_array_ptr)++; //increment pointer to next value
        return 2;
    }

    return 0;
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
     char state_description[16];
     //find correct string to print for state enum
     //new, ready, running, interrupted, waiting, halted, idle
     switch (me->state) {
         case 0:
             strcpy(state_description, "new");
             break;
         case 1:
             strcpy(state_description, "ready");
             break;
         case 2:
             strcpy(state_description, "running");
             break;
         case 3:
             strcpy(state_description, "interrupted");
             break;
         case 4:
             strcpy(state_description, "waiting");
             break;
         case 5:
             strcpy(state_description, "halted");
             break;
         default:
             strcpy(state_description, "idle");
             break;
     }

     char * result = (char *) malloc(sizeof(char) * 1000);
     sprintf(result, "content: PCB_ID: %d, Priority: %d, State: %s, PC: 0x%04X\n",
             me->process_num, me->priority, state_description, me->addressPC);
     return result;
 }
