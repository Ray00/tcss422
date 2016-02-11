//
//  stack.h
//
//  Created by Khoa Doan on 2/07/16.
//  Copyright © 2016 Khoa Doan. All rights reserved.
//  modified by ray
//
#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct stack_struct {
    unsigned int * data_array;
    unsigned int pointer_index;
    unsigned int array_size;
} STACK_STR;
typedef STACK_STR * STACK_STR_p;

STACK_STR_p STACK_constructor(unsigned int);
void STACK_destructor(STACK_STR_p);
void STACK_push(STACK_STR_p, unsigned int);
unsigned int STACK_pop(STACK_STR_p);
unsigned int STACK_peek(STACK_STR_p);

#endif
