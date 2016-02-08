//
//  timer.h
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//
#ifndef TIMER_H_
#define TIMER_H_

#define TIME_SLICE 300

typedef struct timer_struct {
    unsigned int timer;
    unsigned int totalTime;
} *Timer_p;

Timer_p Timer_constructor(void);
int Timer_update(Timer_p);

#endif
