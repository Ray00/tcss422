/*
 * discontinuities.h
 *
 *  Created on: Feb 6, 2016
 *      Author: ray kim
 */




/* DISCONT_constructor
 *
 * Instantiates discontinuities object
 *
 * params:  unsigned int        vector number
 *          enum interrupt_type interrupt type (schedule/timer, IO trap)
 *          handler_fp          handler function specific to this interrupt/trap/exception
 * return:  DISCONT_STR_PTR      self
 */
DISCONT_STR_PTR DISCONT_constructor (unsigned int vector, enum interrupt_type interrupt, handler_fp handler_func) {
    
    DISCONT_STR_PTR self = (DISCONT_STR_PTR) malloc(sizeof(DISCONT_STR));
    
    self->vector = vector;
    self->interrupt = interrupt;
    self->func_ptr = handler_func; //this may not work
    
    return self;
}



/* Function: DISCONT_ISR
 * ------------------------
 * only saves the context of the current process ( CPU state )
 *
 * params:  DISCONT_STR_PTR self
 *          CPU_p   current process
 * return: none
 */
void DISCONT_ISR (DISCONT_STR_PTR self, CPU_p cpu_p) {
    
    //Put PC value into sysStack
    CPU_SysStack_push(cpu_p, cpu_p->pc);
    
    //Change the state of the running process to interrupted,
    PCB_setState(cpu_p->currentProcess, interrupted);
    
    
    //determine if interrupt is caused by IO completion or timer
    switch (self->interrupt) {
        case timer: //FIXME does it make sense to have timer interrupt running while running IO completion handler???

            //Upcall to specific interrupt handler
            self->handler_func(cpu_p);
            break;
        case io:
            //Upcall to specific interrupt handler
            self->handler_func(cpu_p);
            break;
        default:
            puts("Non supported interrupt type.");
            exit();
            break;
    }
    
    //Put PC value from sysStack into pc
    cpu_p->pc = CPU_SysStack_pop(cpu_p); /********* IRET *********/
    
    return;
}


/* Function: DISCONT_TSR
 * ------------------------
 * Trap service routine
 * Calls the appropriate trap service handler
 *
 * params:  CPU_p           cpu
 *          unsigned int    device number
 * return: none
 */
void DISCONT_TSR (CPU_p cpu_p, unsigned int call_device_num) {

    //Put PC value into sysStack
    CPU_SysStack_push(cpu_p, cpu_p->pc);
    
    //put current process' status into "blocked"
    cpu_p->currentProcess->state = blocked; //this should be done in handler
    
    switch (call_device_num) {
        case 1:
            //TODO call trap service handler code here
            //trap handler moves current process into queue for device
            break;
        case 2:
            //TODO call trap service handler code here
            break;
        default:
            puts("No such device.");
            exit();
            break;
    }

    //Put PC value from sysStack into pc
    cpu_p->pc = CPU_SysStack_pop(cpu_p); /********* IRET *********/
    
    return;
}



/* DISCONT_destructor
 *
 * Destroys DISCONT_STR_PTR object
 *
 * params:  DISCONT_STR_PTR
 * return:  none
 */
DISCONT_STR_PTR DISCONT_destructor (DISCONT_STR_PTR self) {
    free (self);
}

