//
//  stack.c
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//

#include "stack.h"

Stack_p Stack_constructor(void) {
    Stack_p me = malloc(sizeof(struct stack_struct));
    if (me != NULL) {
        me->data = malloc(sizeof(unsigned int) * STACK_MAX);
        me->size = 0;
    }
    return me;
}

void Stack_destructor(Stack_p me) {
    free(me->data);
    free(me);
}

void Stack_push(Stack_p me, unsigned int value) {
    if (me->size < STACK_MAX) {
        me->data[me->size++] = (long) value;
    }
}

long Stack_pop(Stack_p me) {
    return (me->size > 0) ? me->data[--me->size] : -1;
}
