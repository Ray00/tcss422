/*
 * cpu.c
 *
 *  Created on: Jan 22, 2016
 *      Author: nabilfadili, raykim
 */

unsigned int G_NEW_PROC_ID = 0;

//FILE *fp;

/*
 * Function:  Main
 * --------------------
 *
 */

void mainLoop(CPU_p self) {

	/*File I/O*/
//	fp = fopen("scheduleTrace.txt", "w+");

    /* round robin simulation */
    while (1) {

        /*****************************************/
        /********* Create new processes **********/
        /*****************************************/
        //create up to 5 new processes
        if (G_NEW_PROC_ID < 30) {
            createNewProcesses(self);
        }
        
        //add newly created processes in self->createdQueue to self->readyQueue
        while (FIFO_size(self->createdQueue) != 0) {
            PCB_p temp_pcb_p = FIFO_dequeue(self->createdQueue);
            PCB_setState(temp_pcb_p, ready);
            FIFO_enqueue(self->readyQueue, temp_pcb_p);

            printf("Process ID: %u Enqueued\n", temp_pcb_p->process_num); //print message that process has been enqueued
//            fprintf(fp, "Process ID: %u Enqueued\n", temp_pcb_p->process_num); //output to file

            puts(PCB_toString(temp_pcb_p)); //print PCB contents
//            fprintf(fp, "%s", PCB_toString(temp_pcb_p)); //output PCB contents
//            fprintf(fp, "\n");
        }
        
        //if current process is IDLE and processes available in readyQueue, load first process in readyQueue into CPU
        if (self->currentProcess == NULL && FIFO_size(self->readyQueue) > 0) {
            self->currentProcess = FIFO_dequeue(self->readyQueue);
            PCB_setState(self->currentProcess, running);
        }

        //pseudo-push PC to the system stack (interrupt does this in reality)
        CPU_SysStack_push(self, self->pc);

        /*****************************************/
        /* Simulated Fetch, Decode, Execute Cycle /
        /*****************************************/

        //check if current PC matches with any IO calls in the 2 IO traps arrays
        unsigned int call_device_num = PCB_currPCHasIOCall(self->currentProcess, self->pc);
        
        //FUTURE TODO add Fetch Decode Execute instructions
        
        
        /*****************************************/
        /********* Check Timer Interrupt *********/
        /*****************************************/
        
        //TODO check if timer interrupt has occured in if statement
        
        DISCONT_STR_PTR timerInterruptHandler = (DISCONT_STR_PTR) malloc(sizeof(DISCONT_STR));
        timerInterruptHandler = DISCONT_constructor(0, timer, TIMER_scheduler);
        DISCONT_ISR(timerInterruptHandler, self); //call interrupt service routine

        
        /*****************************************/
        /**** Check I/O Completion Interrupts ****/
        /*****************************************/

        //TODO check if IO completion interrupt has cocured in if statement
        
        DISCONT_STR_PTR IOCompletionInterruptHandler = (DISCONT_STR_PTR) malloc(sizeof(DISCONT_STR));
        IOCompletionInterruptHandler = DISCONT_constructor(1, io, IO_x_handler);
        DISCONT_ISR(IOCompletionInterruptHandler, self); //call interrupt service routine
        
        /*****************************************/
        /******* Call trap service handler *******/
        /*****************************************/
        if (call_device_num != 0) {
            DISCONT_TSR(self, call_device_num);
        }
        
        /*****************************************/
        /* PC increment & process termination check /
        /*****************************************/
        
        self->pc += 1; //increment cpu pc
        
        //see if pc has incremented over MAX_PC
        if (self->pc > self->currentProcess->max_pc) {
            self->pc = 0;
            PCB_incrementTermCount(self->currentProcess);
        }
        
        //if process has run full course, move to termination stack
        if (PCB_checkTerminate(self->currentProcess)) {
            PCB_terminate(self->currentProcess);
            //move process to termination queue
            self->currentProcess->addressPC = self->pc;
            priority_enqueue(self->terminatedQueue, self->currentProcess);
            //bring in new process from readyqueue
            self->currentProcess = priority_dequeue(self->readyQueue);
            if (self->currentProcess == NULL)
                exit();
            self->pc = self->currentProcess->addressPC;
        }

    }
}


void createNewProcesses(CPU_p self) {
    int random_num_range_0_to_5 = rand() % 6; //create a random number of new processes, between 0 and 5
    
    //place random num processes into cpu_p->createdQueue
    for (int i = 1; i <= random_num_range_0_to_5; i++) {
        
        G_NEW_PROC_ID += 1;
        
        //PCB_constructor(unsigned int pID, unsigned int priority, enum state_type s, unsigned int addPC, unsigned int addSp)
        FIFO_enqueue(self->createdQueue, PCB_constructor(G_NEW_PROC_ID, 1, new, 0, 0));
    }
}

CPU_p CPU_constructor(void) {
    srand((unsigned) time(NULL));
    CPU_p newCPU = (CPU_p) malloc(sizeof(CPU));
    //IDLE = PCB_constructor(G_NEW_PROC_ID, 999, idle, 0, 0);
    newCPU->timer = 0;
    newCPU->pc = 0;
    newCPU->sysStack = (unsigned int *) malloc(sizeof(unsigned int) * STACK_SIZE);
    newCPU->sysStackPointer = newCPU->sysStack;
    newCPU->currentProcess = NULL;
    /* queue instantiation */
    newCPU->readyQueue = FIFO_constructor();
    newCPU->createdQueue = FIFO_constructor(); //newly launched processes queue
    newCPU->terminatedQueue = FIFO_constructor(); //"for deallocation" queue

    return newCPU;
}

void CPU_destructor(CPU_p self) {
    FIFO_destructor(self->readyQueue);
    FIFO_destructor(self->createdQueue);
    FIFO_destructor(self->terminatedQueue);
    PCB_destructor(self->currentProcess);
    free(self);
}

void CPU_setPC(CPU_p self, unsigned int pc) {
    self->pc = pc;
}

unsigned int CPU_getPC(CPU_p self) {
    return self->pc;
}

void CPU_SysStack_push(CPU_p self, unsigned int pc) {
    *(self->sysStackPointer) = pc;
    (self->sysStackPointer)++;
}

unsigned int CPU_SysStack_pop(CPU_p self) {
    (self->sysStackPointer)--;
    return *(self->sysStackPointer);
}

void CPU_setCurrentProcess(CPU_p self, PCB_p pcb) {
    self->currentProcess = pcb;
}

PCB_p CPU_getCurrentProcess(CPU_p self) {
    return self->currentProcess;
}

void CPU_readyQueue_enqueue(CPU_p self, PCB_p pcb) {
    FIFO_enqueue(self->readyQueue, pcb);
}

PCB_p CPU_readyQueue_dequeue(CPU_p self) {
    return FIFO_dequeue(self->readyQueue);
}

void CPU_createdQueue_enqueue(CPU_p self, PCB_p pcb) {
    FIFO_enqueue(self->createdQueue, pcb);
}

PCB_p CPU_createdQueue_dequeue(CPU_p self) {
    return FIFO_dequeue(self->createdQueue);
}

void CPU_terminatedQueue_enqueue(CPU_p self, PCB_p pcb) {
    FIFO_enqueue(self->terminatedQueue, pcb);
}

PCB_p CPU_terminatedQueue_dequeue(CPU_p self) {
    return FIFO_dequeue(self->terminatedQueue);
}

char* CPU_toString(CPU_p self) {
    char * result = (char *) malloc(sizeof(char) * 1000);
    sprintf(result, "Current PC: %u\nCurrent sysStack: %d\nCurrent Process: \n"
            "ReadyQueue Size: \nCreatedQueue Size: \nTerminatedQueue Size: \n", self->pc, self->sysStack);
    return result;
}

//void CPU_timerInterruptHandler(CPU_p self, enum interrupt_type itype) {
//    //1.) Change the state of the running process to interrupted,
//    PCB_setState(self->currentProcess, interrupted); 
//    //2.) Save the CPU state to the PCB for that process (PC value)
//    PCB_setPC(self->currentProcess, self->pc);
//    //3.) Upcall to scheduler
//    CPU_scheduler(self, itype);
//    //4.) Put PC value from sysStack into pc
//    self->pc = CPU_SysStack_pop(self); /********* IRET *********/
//
//    //5.) Return
//    return;
//}

/******* the code below should be moved to timer class *******/
void CPU_scheduler(CPU_p self) {

    //1.) Change its state from interrupted to ready
    self->currentProcess->state = ready;
    //2.) Put the process back into the ready queue (if not idle process)
    if (self->currentProcess != NULL) {
        FIFO_enqueue(self->readyQueue, self->currentProcess);
    }

    //3.) Upcall to dispatcher
    CPU_dispatcher(self);
    //4.) Additional house keeping
    //future TODO

    //4.) Return - Chance to do more before returning but nothing yet
    return;
}

/******* the code below should be moved to timer class *******/
void CPU_dispatcher(CPU_p self) {
    PCB_p next_process_p = FIFO_dequeue(self->readyQueue);
    PCB_p last_process_p = self->currentProcess;

    //1.) Save the state of the current process into its PCB (here we mean the PC value)
    /*NOT SURE WHY WE NEED TO DO THIS AGAIN?*/

    //every fourth context switch
    if (G_LOOP_ITER_NUM % 4 == 0) {
        printf("Interrupted Process: %s", PCB_toString(last_process_p)); //print the contents of the running process
        printf("Switching to: %s\n", PCB_toString(next_process_p)); //print contents of the ready queue head PCB

        fprintf(fp, "Interrupted Process: %s", PCB_toString(last_process_p)); //output contents of running process
        fprintf(fp, "Switching to: %s\n", PCB_toString(next_process_p)); //output contents of ready queue head
    }

    //2.) Dequeue the next waiting process (PCB)
    self->currentProcess = next_process_p;
    //3.) Change its state to running
    PCB_setState(self->currentProcess, running);
    //4.) Copy its PC value (and SW if you implement it) to the SysStack location to replace the PC of the interrupted process
    CPU_SysStack_push(self, PCB_getPC(self->currentProcess));

    //after context switch
    if (G_LOOP_ITER_NUM % 4 == 0) {
        printf("Last Process: %s", PCB_toString(last_process_p)); //print the contents of the last process
        printf("Current Process: %s", PCB_toString(next_process_p)); //print contents of current process
        printf("Ready Queue: %s\n\n", FIFO_toString(self->readyQueue));

        fprintf(fp, "Last Process: %s", PCB_toString(last_process_p)); //print the contents of the last process
        fprintf(fp, "Current Process: %s", PCB_toString(next_process_p)); //print contents of current process
        fprintf(fp, "Ready Queue: %s\n\n", FIFO_toString(self->readyQueue));
    }

    //5.) Return
    return;
}

int main() {
    CPU_p cpu = CPU_constructor();
    
//    printf(CPU_toString(cpu));

//    unsigned int testPC = 3000;
//    CPU_setPC(cpu, testPC);
//    printf("\nsetPC Test: %u", CPU_getPC(cpu));

//    PCB_p testEnqueuePCB = PCB_constructorWithEmpty();
//    CPU_readyQueue_enqueue(cpu, testEnqueuePCB);
//    PCB_p testDequeuePCB = CPU_readyQueue_dequeue(cpu);
//    printf("\nDequeue PCB Test: %s\n", PCB_toString(testDequeuePCB));
    mainLoop(cpu);
    CPU_destructor(cpu);
    exit(0);
}
