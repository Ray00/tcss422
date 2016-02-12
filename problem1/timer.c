//
//  timer.c
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//  modified by ray
//

#include "timer.h"

TIMER_STR_p TIMER_constructor() {
    TIMER_STR_p this = malloc(sizeof(TIMER_STR));
    this->elapsed_cycles = 0;
    return this;
}

void TIMER_destructor(TIMER_STR_p this) {
    free(this);
}

/* Function: TIMER_updateCheckCompletion
 * -----------------------
 * Decrements remaining time slice, returning 1 if time slice is over or 0 in the case the time remains for this process
 *
 * params:  TIMER_STR_p        this
 * return:  int            0 if process has cycles remaining, 1 if no cycles remaining
 */
int TIMER_updateCheckCompletion(TIMER_STR_p this) {
    this->elapsed_cycles++;
    if (this->elapsed_cycles > TIME_QUANTUM) {
        //reset timer for next process
        this->elapsed_cycles = 0;
        return 1;
    }
    return 0;
}


/* Function: TIMER_reset
 * -----------------------
 * resets elapsed_cycles to 0. typically called after IO device call
 *
 * params:  TIMER_STR_p        this
 * return:  none
 */
void TIMER_reset(TIMER_STR_p this) {
    this->elapsed_cycles = 0;
}


