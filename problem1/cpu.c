/***************************************************************************
* cpu.c
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

#include "cpu.h"
#include "discontinuities.h"

/*Sets max amount of IO process to be created.
 *PID RANGE: 0 - 49*/
unsigned int GLOBAL_NEW_IO_PROC_ID = 0;
unsigned int GLOBAL_NEW_IO_PROC_ID_MAX = 49;

/*Sets max amount of cpu intensive 'dummy' process to be created.
 *PID RANGE: 50 - 74*/
unsigned int GLOBAL_NEW_INTENSIVE_PROC_ID = 50;
unsigned int GLOBAL_NEW_INTENSIVE_PROC_ID_MAX = 74;

/*Sets max amount of cpu intensive realistic process to be created.
 *PID RANGE: 75 - 84*/
unsigned int GLOBAL_NEW_REALISTIC_PROC_ID = 75;
unsigned int GLOBAL_NEW_REALISTIC_PROC_ID_MAX = 84;

char * message_buffer_p;
PCB_p GLOBAL_IDLE_process;

/*
 * Function:  Main
 * --------------------
 *
 */
void CPU_cycle(CPU_p this, DISCONT_STR_p timerInterrupt, DISCONT_STR_p IOCompletionInterrupt, DISCONT_STR_p IO_device_1, DISCONT_STR_p IO_device_2) {

    unsigned int call_device_num;

    /* round robin simulation */
    while (1) {
        /*****************************************/
        /********* Create new processes **********/
        /*****************************************/
        //create up to 5 new IO processes
        if (GLOBAL_NEW_IO_PROC_ID <= GLOBAL_NEW_IO_PROC_ID_MAX) {
            createNewIOProcesses(this);
        }
        //create up to 5 new INTENSIVE processes
        if (GLOBAL_NEW_INTENSIVE_PROC_ID <= GLOBAL_NEW_INTENSIVE_PROC_ID_MAX) {
            createNewIntensiveProcesses(this);
        }
        //create up to 5 new PRODUCER/CONSUMER processes
        if (GLOBAL_NEW_REALISTIC_PROC_ID <= GLOBAL_NEW_REALISTIC_PROC_ID_MAX) {
            //createNewRealisticProcesses(this);
        }

        //add newly created processes in this->createdQueue to this->readyQueue
        while (FIFO_size(this->createdQueue) != 0) {
            PCB_p temp_pcb_p = FIFO_dequeue(this->createdQueue);
            PCB_setState(temp_pcb_p, ready);
            FIFO_enqueue(this->readyQueue, temp_pcb_p);
//            printf("Process ID: %u Enqueued\n", temp_pcb_p->process_num); //print message that process has been enqueued
//            PCB_toString(temp_pcb_p, message_buffer_p);
//            puts(message_buffer_p); //print PCB contents
        }

        //if current process is IDLE and processes available in readyQueue, load first process in readyQueue into CPU
        if (this->currentProcess == GLOBAL_IDLE_process && FIFO_size(this->readyQueue) > 0) {
            this->currentProcess = FIFO_dequeue(this->readyQueue);
            PCB_setState(this->currentProcess, running);
        }

        /******************************************/
        /* Simulated Fetch, Decode, Execute Cycle */
        /******************************************/
        //check if current PC matches with any IO calls in the 2 IO traps arrays
        //NOTE: New for final project!
        //If the io_arrays are NULL then this is a compute intensive process with no IO.
        if (this->currentProcess->io_1_array_ptr != NULL && this->currentProcess->io_1_array_ptr != NULL) {
        	call_device_num = PCB_currPCHasIOCall(this->currentProcess, this->pc);
        }
        else {
        	call_device_num = -1;
        }
        //FUTURE TODO add Fetch Decode Execute instructions

        /*****************************************/
        /********* Check Timer Interrupt *********/
        /*****************************************/

        if (TIMER_updateCheckCompletion(this->timer)) {
        	int oldPID = this->currentProcess->process_num;
            //Put PC value into sysStack
            STACK_push(this->sysStack, this->pc);

            DISCONT_ISR(timerInterrupt, this); //call interrupt service routine

            //Put PC value from sysStack into pc
            this->pc = STACK_pop(this->sysStack); /********* IRET *********/
	    printf("Timer interrupt: PID %u was running, PID %u dispatched\n", oldPID, this->currentProcess->process_num);

        }

        /*****************************************/
        /**** Check I/O Completion Interrupts ****/
        /*****************************************/

        //the two ifs below are poorly coded, but can't find a way around it without creating another function
        if (IO_updateCheckCompletion(IO_device_1->interrupting_device)) {
        	printf("I/O completion interrupt: PID %u is running", this->currentProcess->process_num);
            STACK_push(this->sysStack, this->pc); //Put PC value into sysStack
            DISCONT_setInterruptingDevice(IOCompletionInterrupt, IO_device_1->interrupting_device);
            DISCONT_ISR(IOCompletionInterrupt, this); //call ISR
            this->pc = STACK_pop(this->sysStack); /********* IRET *********/

        }

        if (IO_updateCheckCompletion(IO_device_2->interrupting_device)) {
        	printf("I/O completion interrupt: PID %u is running", this->currentProcess->process_num);
            STACK_push(this->sysStack, this->pc); //Put PC value into sysStack
            DISCONT_setInterruptingDevice(IOCompletionInterrupt, IO_device_2->interrupting_device);
            DISCONT_ISR(IOCompletionInterrupt, this);
            this->pc = STACK_pop(this->sysStack); /********* IRET *********/
        }

        /*****************************************/
        /****** Call IO trap service handler *****/
        /*****************************************/
        //NOTE: New in Final Project
        //Will only enter these blocks if a call device number was generated
        if (call_device_num == 1) {
        	printf("I/O trap request: I/O device 1");
            STACK_push(this->sysStack, this->pc); //Put PC value into sysStack
            DISCONT_TSR(IO_device_1, this);
            this->pc = STACK_pop(this->sysStack); /********* IRET *********/
        } else if (call_device_num == 2) {
        	printf("I/O trap request: I/O device 2");
            STACK_push(this->sysStack, this->pc); //Put PC value into sysStack
            DISCONT_TSR(IO_device_2, this);
            this->pc = STACK_pop(this->sysStack); /********* IRET *********/
        }

        /********************************************/
        /* PC increment & process termination check */
        /********************************************/

        this->pc += 1; //increment cpu pc

        //see if pc has incremented over MAX_PC
        if (this->pc > this->currentProcess->max_pc) {
            this->pc = 0;
            PCB_incrementTermCount(this->currentProcess);
        }

        //if process has run full course, move to termination stack
        if (PCB_checkTerminate(this->currentProcess)) {

            PCB_terminate(this->currentProcess);
        	printf("Process terminated: PID %u at %ld\n", this->currentProcess->process_num, (long)this->currentProcess->termination);

            //move process to termination queue
            this->currentProcess->addressPC = this->pc;
            FIFO_enqueue(this->terminatedQueue, this->currentProcess);
            //bring in new process from readyqueue
	    if (FIFO_size(this->readyQueue) > 0) {
		this->currentProcess = FIFO_dequeue(this->readyQueue);
	    } else {
		this->currentProcess = GLOBAL_IDLE_process;
	    }

            this->pc = this->currentProcess->addressPC;
        }

        //print ready queue status
//        FIFO_toString(this->readyQueue, message_buffer_p);
//        printf("Ready Queue: %s\n\n", message_buffer_p);
    }
}


void createNewIOProcesses(CPU_p this) {
    int random_num_range_0_to_5 = (rand() % 6) + 1; //create a random number of new processes, between 0 and 5
    int i;

    //place random num processes into cpu_p->createdQueue
    PCB_p newPCB = NULL;
    for (i = 1; i <= random_num_range_0_to_5; i++) {
        GLOBAL_NEW_IO_PROC_ID += 1;
        //PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSp)
        newPCB = PCB_constructor(GLOBAL_NEW_IO_PROC_ID, 1, new, 0, 0, 0, rand());
        printf("I/O process created: PID %d at %ld\n", newPCB->process_num, (long)this->currentProcess->creation);
        FIFO_enqueue(this->createdQueue, newPCB);
    }
}

void createNewIntensiveProcesses(CPU_p this) {
    int random_num_range_0_to_5 = (rand() % 6) + 1; //create a random number of new processes, between 0 and 5
    int i;

    //place random num processes into cpu_p->createdQueue
    PCB_p newPCB = NULL;
    for (i = 1; i <= random_num_range_0_to_5; i++) {
        GLOBAL_NEW_INTENSIVE_PROC_ID += 1;

        //NOTE: Priority = 0
        newPCB = PCB_constructor(GLOBAL_NEW_INTENSIVE_PROC_ID, 0, new, 0, 0, 0, rand());
        newPCB->io_1_array_ptr = NULL;  //Call free(newPCB->io_1_traps); ???
        newPCB->io_2_array_ptr = NULL;  //Call free(newPCB->io_2_traps); ???
        printf("Compute intensive process created: PID %d at %ld\n", newPCB->process_num, (long)this->currentProcess->creation);
        FIFO_enqueue(this->createdQueue, newPCB);
    }
}

void createNewRealisticProcesses(CPU_p this) {
    //TODO: Producer consumer pair creation.
}

CPU_p CPU_constructor(void) {
    srand((unsigned) time(NULL));
    CPU_p newCPU = (CPU_p) malloc(sizeof(CPU));
    //IDLE = PCB_constructor(G_NEW_PROC_ID, 999, idle, 0, 0);
    newCPU->timer = TIMER_constructor();
    newCPU->pc = 0;
    newCPU->sysStack = STACK_constructor(200);
    newCPU->currentProcess = NULL;
    /* queue instantiation */
    newCPU->readyQueue = FIFO_constructor();
    newCPU->createdQueue = FIFO_constructor(); //newly launched processes queue
    newCPU->terminatedQueue = FIFO_constructor(); //"for deallocation" queue

    return newCPU;
}

void CPU_destructor(CPU_p this) {
    TIMER_destructor(this->timer);
    STACK_destructor(this->sysStack);
    FIFO_destructor(this->readyQueue);
    FIFO_destructor(this->createdQueue);
    FIFO_destructor(this->terminatedQueue);
    PCB_destructor(this->currentProcess);
    free(this);
}

void CPU_setPC(CPU_p this, unsigned int pc) {
    this->pc = pc;
}

unsigned int CPU_getPC(CPU_p this) {
    return this->pc;
}
//
//void CPU_SysStack_push(CPU_p this, unsigned int pc) {
//    *(this->sysStackPointer) = pc;
//    (this->sysStackPointer)++;
//}
//
//unsigned int CPU_SysStack_pop(CPU_p this) {
//    (this->sysStackPointer)--;
//    return *(this->sysStackPointer);
//}

void CPU_setCurrentProcess(CPU_p this, PCB_p pcb) {
    this->currentProcess = pcb;
}

PCB_p CPU_getCurrentProcess(CPU_p this) {
    return this->currentProcess;
}

void CPU_readyQueue_enqueue(CPU_p this, PCB_p pcb) {
    FIFO_enqueue(this->readyQueue, pcb);
}

PCB_p CPU_readyQueue_dequeue(CPU_p this) {
    return FIFO_dequeue(this->readyQueue);
}

void CPU_createdQueue_enqueue(CPU_p this, PCB_p pcb) {
    FIFO_enqueue(this->createdQueue, pcb);
}

PCB_p CPU_createdQueue_dequeue(CPU_p this) {
    return FIFO_dequeue(this->createdQueue);
}

void CPU_terminatedQueue_enqueue(CPU_p this, PCB_p pcb) {
	FIFO_enqueue(this->terminatedQueue, pcb);
}

PCB_p CPU_terminatedQueue_dequeue(CPU_p this) {
    return FIFO_dequeue(this->terminatedQueue);
}

char* CPU_toString(CPU_p this) {
    char * result = (char *) malloc(sizeof(char) * 1000);
    sprintf(result, "Current PC: %u\nCurrent sysStack: %d\nCurrent Process: \nReadyQueue Size: \nCreatedQueue Size: \nTerminatedQueue Size: \n", this->pc, STACK_peek(this->sysStack));
    return result;
}


int main() {
    srand(time(NULL));

    //create interrupt objects
    CPU_p cpu = CPU_constructor();
    DISCONT_STR_p timerInterrupt;
    DISCONT_STR_p IOCompletionInterrupt;
    DISCONT_STR_p keyboard_trap_handler;
    DISCONT_STR_p monitor_trap_handler;

    message_buffer_p = (char *) malloc(sizeof(char) * 1000);

    //create IDLE process
    GLOBAL_IDLE_process = PCB_constructor(999, 999, idle, 0, 0, 0, 0);
    GLOBAL_IDLE_process->io_1_traps[0] = 0xFFFFFFFF;
    GLOBAL_IDLE_process->io_2_traps[0] = 0xFFFFFFFF;
    cpu->currentProcess = GLOBAL_IDLE_process; //set first process as idle

    timerInterrupt = DISCONT_constructor(0, timer);
    IOCompletionInterrupt = DISCONT_constructor(1, io_completion);
    DISCONT_STR_p io_device_1 = DISCONT_constructor(2, io_handler_1);
    DISCONT_STR_p io_device_2 = DISCONT_constructor(3, io_handler_2);

    IO_STR_p keyboard_trap = IO_constructor();
    IO_STR_p monitor_trap = IO_constructor();

    //set place keyboard/monitor trap objects into discont wrappers
    DISCONT_setInterruptingDevice(io_device_1, keyboard_trap);
    DISCONT_setInterruptingDevice(io_device_2, monitor_trap);

    //run processes (will run infinitely if there's a PCB with terminate = 0)
    CPU_cycle(cpu, timerInterrupt, IOCompletionInterrupt, io_device_1, io_device_2);

    //destroy objects
    DISCONT_destructor(timerInterrupt);
    DISCONT_destructor(IOCompletionInterrupt);
    DISCONT_destructor(io_device_1);
    DISCONT_destructor(io_device_2);
    IO_destructor(keyboard_trap);
    IO_destructor(monitor_trap);
    CPU_destructor(cpu);
    exit(0);
}
