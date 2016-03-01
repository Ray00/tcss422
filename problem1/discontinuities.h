/***************************************************************************
* discontinuities.h
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

#ifndef DISCONTINUITIES_H
#define DISCONTINUITIES_H

#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"
#include "fifoqueue.h"
#include "priorityqueue.h"
#include "cpu.h"
#include "IO_x.h"
#include "timer.h"

typedef enum interrupt_type_enum {
    timer = 0,
    io_completion = 1,
    io_handler_1 = 2,
    io_handler_2 = 3
} Interrupt_type;

typedef struct discontinuities_str {
    unsigned int vector; //aka trap service routine number
    Interrupt_type interrupt;
    IO_STR_p interrupting_device;
    //void (*handler_fp)(CPU_P); //pointer to handler function

} DISCONT_STR;
typedef DISCONT_STR * DISCONT_STR_p;

/*** function pointer signature used for all handler functions ***/
//typedef void (*handler_fp)(CPU_p);

/*** prototypes ***/
DISCONT_STR_p DISCONT_constructor (unsigned int, Interrupt_type);
void DISCONT_destructor (DISCONT_STR_p);
void DISCONT_setInterruptingDevice (DISCONT_STR_p, IO_STR_p);
IO_STR_p DISCONT_getInterruptingDevice (DISCONT_STR_p);
void DISCONT_ISR (DISCONT_STR_p, CPU_p);
void DISCONT_TSR (DISCONT_STR_p, CPU_p);
void DISCONT_IVT (DISCONT_STR_p, CPU_p);

void DISCONT_scheduler (DISCONT_STR_p, CPU_p);
void DISCONT_dispatcher (CPU_p);


#endif /* DISCONTINUITIES_H */
