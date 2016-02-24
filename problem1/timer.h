/***************************************************************************
* timer.h
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
// haha

#endif
