/*
 * discontinuities.h
 *
 *  Created on: Feb 6, 2016
 *      Author: ray kim
 *
 *  stack overflow: 1350376
 */

#ifndef DISCONTINUITIES_H
#define DISCONTINUITIES_H

#include <time.h>
#include <unistd.h>
#include "pcb.h"
#include "cpu.h"

typedef struct discontinuities_str {
    unsigned int vector; //aka trap service routine number
    enum interrupt_type interrupt;
    void (*handler_fp)(CPU_P); //pointer to handler function
    
} DISCONT_STR;
typedef DISCONT_STR * DISCONT_STR_PTR;

/*** function pointer signature used for all handler functions ***/
typedef void (*handler_fp)(CPU_P);

/*** prototypes ***/
DISCONT_STR_PTR DISCONT_constructor (unsigned int, enum interrupt_type, handler_fp);

void DISCONT_ISR (DISCONT_STR_PTR, CPU_P);
void DISCONT_TSR (CPU_p, unsigned int);

void DISCONT_destructor (DISCONT_STR_PTR);




#endif /* DISCONTINUITIES_H */