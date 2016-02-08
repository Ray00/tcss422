//
//  timer.c
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "timer.h"

Timer_p Timer_constructor() {
    Timer_p me = malloc(sizeof(struct timer_struct));
    me->timer = TIME_SLICE;
    me->totalTime = 0;
}

void Timer_destructor(Timer_p me) {
    free(me);
}

int Timer_update(Timer_p me) {
    me->timer--;
    me->totalTime++;
    if (me->timer == 0) {
        me->timer = TIME_SLICE;
        return 1;
    }
    return 0;
}
