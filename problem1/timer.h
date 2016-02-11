//
//  timer.h
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//  modified by ray
//
#ifndef TIMER_H_
#define TIMER_H_

#include <stdlib.h>

#define TIME_QUANTUM 300

typedef struct timer_struct {
    unsigned int elapsed_cycles;
} TIMER_STR;
typedef TIMER_STR * TIMER_STR_p;

TIMER_STR_p TIMER_constructor(void);
void TIMER_destructor(TIMER_STR_p);
int TIMER_updateCheckCompletion(TIMER_STR_p);
void TIMER_reset(TIMER_STR_p);


#endif
