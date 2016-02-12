//
//  stack.h
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//
#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>

#define STACK_MAX 500

typedef struct stack_struct {
    long *data;
    int size;
} *Stack_p;

Stack_p Stack_constructor(void);
void Stack_destructor(Stack_p);
void Stack_push(Stack_p, unsigned int);
long Stack_pop(Stack_p);

#endif
