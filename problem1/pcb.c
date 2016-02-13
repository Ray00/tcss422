/***************************************************************************
* pcb.c
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
PCB_p PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSW, unsigned int addSp, unsigned int randForTerminate) {
    PCB_p result = (PCB_p) malloc(sizeof(PCB));


    if (result != NULL) {
        result->process_num = pID;
        result->priority = priority;
        result->state = s;
        result->addressPC = addPC;
        result->addressSW = addSW;
        result->addressSpace = addSp;
        result->max_pc = MAX_PC;
        result->terminate = randForTerminate % 6; //generate random terminate number
        result->term_count = 0;

        //Get the creation time
        result->creation = PCB_getTimestamp();



        //create I/O trap call arrays
        result->io_1_traps = PCB_create_trap_call_array(MAX_CALLS_FOR_IO);
        result->io_1_array_ptr = result->io_1_traps;
        result->io_2_traps = PCB_create_trap_call_array(MAX_CALLS_FOR_IO);
        result->io_2_array_ptr = result->io_2_traps;

    }

    return result;

}


/* Function: PCB_create_trap_call_array
 * ------------------------
 * creates an array of instructions (randomly) at which I/O device traps are called
 *
 * params:  unsigned int number of elements in array
 * return: none
 */
unsigned int * PCB_create_trap_call_array (unsigned int num_elements_in_array) {

    int i = 0;
    int j = 0;
    int temp = 0;
    int check = 0;
    unsigned int * array_ptr;

    array_ptr = (unsigned int *) malloc(sizeof(unsigned int) * num_elements_in_array);

    temp = rand() % MAX_PC;
    array_ptr[0] = temp;
    //printf("%d\n", temp);
    for (i = 1; i < 4; i++) {
        temp = rand() % MAX_PC;
        //printf("%d\n", temp);
        check = 0;
        for (j = 0; j < i; j++) {
            if (temp == array_ptr[j]) {
                check = 1;
            }
        }
        if (check == 0) {
            array_ptr[i] = temp;
        } else {
            i--;
        }
    }


    //Sort Traps calls
    i = 0;
    j = 0;
    temp = 0;
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            if (array_ptr[i] > array_ptr[j]) {
                temp =  array_ptr[i];
                array_ptr[i] = array_ptr[j];
                array_ptr[j] = temp;
            }
        }
    }

    return array_ptr;
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
    free(p->io_1_traps);
    free(p->io_2_traps);
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
    if (this->terminate == 0) {
        return 0;
    } else if (this->terminate == this->term_count) {
        return 1;
    }

    return 0;
}


void PCB_terminate(PCB_p this) {

    //Set termination time
    this->termination = PCB_getTimestamp();
    this->state = halted;
    
}


void PCB_incrementTermCount(PCB_p this) {
  this->term_count++;
}

/*
 * Function:  PCB_getTimestamp
 * --------------------
 * Returns unix time stamp
 *
 *
 * params:	none
 * return:  struct time_t * struct which contains timestamp data type
 */
struct tm * PCB_getTimestamp(void) {
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    
    return timeinfo;
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

    //check if PC matches either values pointed to by IO call array pointers
    if (pc == *(this->io_1_array_ptr)) { ;//bounds checking to stay within io_1_traps


	//reset io_array_ptr's once they have reached the last element
    	if (this->io_1_array_ptr == this->io_1_traps + MAX_CALLS_FOR_IO - 1) {
		this->io_1_array_ptr = this->io_1_traps;
    	} else {
		(this->io_1_array_ptr)++; //increment pointer to next value
	}

        return 1;
    } else if (pc == *(this->io_2_array_ptr)) { //bounds checking to stay within io_2_traps
	//reset io_array_ptr's once they have reached the last element
    	if (this->io_2_array_ptr == this->io_2_traps + MAX_CALLS_FOR_IO - 1) {
		this->io_2_array_ptr = this->io_2_traps;
    	} else {
		(this->io_2_array_ptr)++; //increment pointer to next value
	}

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
 *          char * result the buffer the output message is written to
 */
 void PCB_toString(PCB_p this, char * result) {
     char state_description[16];
     //find correct string to print for state enum
     //new, ready, running, interrupted, waiting, halted, idle
     switch (this->state) {
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

     sprintf(result, "content: PCB_ID: %d, Priority: %d, State: %s, PC: 0x%04X \nCycles before termination: %d, Current cycle number: %d\n", this->process_num, this->priority, state_description, this->addressPC, this->terminate, this->term_count);
 }
