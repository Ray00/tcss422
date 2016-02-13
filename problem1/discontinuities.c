/*
 * discontinuities.h
 *
 *  Created on: Feb 6, 2016
 *      Author: ray kim
 */

#include "discontinuities.h"


/* DISCONT_constructor
 *
 * Instantiates discontinuities object
 *
 * params:  unsigned int        vector number
 *          enum interrupt_type interrupt type (schedule/timer, IO trap)
 *          handler_fp          handler function specific to this interrupt/trap/exception
 * return:  DISCONT_STR_p      this
 */
DISCONT_STR_p DISCONT_constructor (unsigned int vector, Interrupt_type interrupt) {
    
    DISCONT_STR_p this = (DISCONT_STR_p) malloc(sizeof(DISCONT_STR));
    
    this->vector = vector;
    this->interrupt = interrupt;
    this->interrupting_device = NULL;
    //this->func_ptr = handler_func; //this may not work
    
    return this;
}

/* DISCONT_destructor
 *
 * Destroys DISCONT_STR_p object
 *
 * params:  DISCONT_STR_p
 * return:  none
 */
void DISCONT_destructor (DISCONT_STR_p this) {
    free (this);
}

/* DISCONT_setInterruptingDevice
 *
 * sets interrupting device field
 *
 * params:  DISCONT_STR_p this
 *          IO_STR_p interrupting_device
 * return:  none
 */
void DISCONT_setInterruptingDevice (DISCONT_STR_p this, IO_STR_p interrupting_device) {
    this->interrupting_device = interrupting_device;
}

/* DISCONT_getInterruptingDevice
 *
 * gets interrupting device field
 *
 * params:  DISCONT_STR_p this
 * return:  IO_STR_p interrupting_device
 */
IO_STR_p DISCONT_getInterruptingDevice (DISCONT_STR_p this) {
    return this->interrupting_device;
}

/* Function: DISCONT_ISR
 * ------------------------
 * only saves the context of the current process ( CPU state )
 *
 * params:  DISCONT_STR_p   this
 *          CPU_p           main cpu object
 * return: none
 */
void DISCONT_ISR (DISCONT_STR_p this, CPU_p cpu_p) {
    
    //1.) Change the state of the running process to interrupted
    if (cpu_p->currentProcess != GLOBAL_IDLE_process)
    	PCB_setState(cpu_p->currentProcess, interrupted);

    //2.) Save the CPU state to the PCB for that process (PC value)
    PCB_setPC(cpu_p->currentProcess, cpu_p->pc);
    
    //3.) Upcall to scheduler (via IVT)
    DISCONT_scheduler(this, cpu_p);
    
    return;
}


/* Function: DISCONT_TSR
 * ------------------------
 * Trap service routine
 * Calls the appropriate trap service handler
 *
 * params:  DISCONT_STR_p   this
 *          STACK_STR_p     stack object
 * return: none
 */
void DISCONT_TSR (DISCONT_STR_p this, CPU_p cpu_p) {
    
    //1.) Change the state of the running process to interrupted
    PCB_setState(cpu_p->currentProcess, waiting);
    
    //place current process into device waitingQueue
    IO_STR_p interruptingDevice = DISCONT_getInterruptingDevice(this);
    printf(", PID %u put into waiting queue", cpu_p->currentProcess->process_num);
    IO_addProcess(DISCONT_getInterruptingDevice(this), cpu_p->currentProcess);
    
    //pop pc stored in sysStack into PCB of last running process (now in IO waitingQueue)
    PCB_setPC(cpu_p->currentProcess, STACK_pop(cpu_p->sysStack));
    
    //schedule must now grab a process from the readyQueue and make it the actively running process
    DISCONT_scheduler(this, cpu_p);
    
    return;
}


/* Function: DISCONT_IVT
 * ------------------------
 * Interrupt vector table (presence is just notional at best)
 * calls the correct route based on vector number (contained wihtin DISCONT object
 *
 * params:  DISCONT_STR_p   this
 *          unsigned int    vector which will lead to corresponding procedure
 *          CPU_p           main cpu object
 * return: none
 */
//void DISCONT_IVT (DISCONT_STR_p this, CPU_p cpu_p) {
//    
//    switch (this->vector) {
//        case timer:
//            DISCONT_scheduler(this, cpu_p);
//            break;
//        case io_completion:
//            DISCONT_scheduler(this, cpu_p);
//            break;
//        case io_handler_1:
//            
//            DISCONT_scheduler(this, cpu_p);
//            break;
//        case io_handler_2:
//            DISCONT_scheduler(this, cpu_p);
//            break;
//        default:
//            puts("This interrupt is not supported");
//            exit(2);
//            break;
//    }
//}


/* DISCONT_scheduler
 *
 * if called by timer           do a context switch
 * if called by io_completion   moves io completed process into ready queue
 * if called by io_handler      moves process requesting IO into waiting queue of IO device
 *
 * params:  DISCONT_STR_p       this
 *          CPU_p               main cpu object
 * return:  none
 */
void DISCONT_scheduler(DISCONT_STR_p this, CPU_p cpu_p) {
    PCB_p unblocked_process;
    switch (this->vector) {
        case timer:
            if (cpu_p->currentProcess != NULL && cpu_p->currentProcess->priority < 30) {
		//1.) Change its state from interrupted to ready
            	cpu_p->currentProcess->state = ready;
            	//2.) Put the process back into the ready queue (if not idle process)
	    	FIFO_enqueue(cpu_p->readyQueue, cpu_p->currentProcess);
	}
                
            //3.) Upcall to dispatcher
            DISCONT_dispatcher(cpu_p);
            //4.) Additional house keeping
            //future TODO
            break;
        case io_completion:
//        	printf("%d\n\n", this->interrupting_device->elapsed_cycles);
            unblocked_process = IO_dequeue_waitQueue(DISCONT_getInterruptingDevice(this));
            printf(", PID %u put in ready queue\n", unblocked_process->process_num);
            FIFO_enqueue(cpu_p->readyQueue, unblocked_process);
            break;
        default: //io call handler
            //grab new process to run
            cpu_p->currentProcess = FIFO_dequeue(cpu_p->readyQueue);
            //push pc of newly dequeued readyQueue process int sysStack
            if (cpu_p->currentProcess != NULL) {
                PCB_setState(cpu_p->currentProcess, running);
            } else {
		cpu_p->currentProcess = GLOBAL_IDLE_process;
            }

	    STACK_push(cpu_p->sysStack, PCB_getPC(cpu_p->currentProcess));            

            //reset timer
            TIMER_reset(cpu_p->timer);

	    //print dispatched information
	    printf(", PID %u dispatched\n", cpu_p->currentProcess->process_num);

            break;
    }
    

    //Return - Chance to do more before returning but nothing yet
    return;
}


void DISCONT_dispatcher(CPU_p cpu_p) {
    PCB_p next_process_p = FIFO_dequeue(cpu_p->readyQueue);
    PCB_p last_process_p = cpu_p->currentProcess;
    char * message_buffer_p = (char *) malloc(sizeof(char) * 1000);
    
    //1.) Save the state of the current process into its PCB (here we mean the PC value)
    /*NOT SURE WHY WE NEED TO DO THIS AGAIN?*/
    
    //every fourth context switch
    if (GLOBAL_NEW_PROC_ID % 4 == 0) {
        PCB_toString(last_process_p, message_buffer_p);
        printf("Interrupted Process: %s", message_buffer_p); //print the contents of the running process
        PCB_toString(last_process_p, message_buffer_p);
        printf("Switching to: %s\n", message_buffer_p); //print contents of the ready queue head PCB
        
    }
    //Put PC value from sysStack into last running process that has just been placed into the readyqueue in the scheduler function
    PCB_setPC(cpu_p->currentProcess, STACK_pop(cpu_p->sysStack));
    //2.) Dequeue the next waiting process (PCB)
    cpu_p->currentProcess = next_process_p;

    if (cpu_p->currentProcess != NULL) { //if currentProcess is null(IDLE)
        //3.) Change its state to running
        PCB_setState(cpu_p->currentProcess, running);
    } else {
        cpu_p->currentProcess = GLOBAL_IDLE_process;
    }
    
    //4.) Copy its PC value (and SW if you implement it) to the SysStack location to replace the PC of the interrupted process
    STACK_push(cpu_p->sysStack, PCB_getPC(cpu_p->currentProcess));

    //after context switch
    if (GLOBAL_NEW_PROC_ID % 4 == 0) {
        PCB_toString(last_process_p, message_buffer_p);
        printf("Last Process: %s", message_buffer_p); //print the contents of the last process
        PCB_toString(next_process_p, message_buffer_p);
        printf("Current Process: %s", message_buffer_p); //print contents of current process
//        FIFO_toString(cpu_p->readyQueue, message_buffer_p);
//        printf("Ready Queue: %s\n\n", message_buffer_p);
    }
    
    free(message_buffer_p);
    //5.) Return
    return;
}
