/***************************************************************************
* stack.c
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

#include "stack.h"

STACK_STR_p STACK_constructor(unsigned int stack_size) {
    STACK_STR_p this = (STACK_STR_p) malloc(sizeof(STACK_STR));
    if (this != NULL) {
        this->data_array = (unsigned int *) malloc(sizeof(unsigned int) * stack_size);
        this->pointer_index = 0;
        this->array_size = stack_size;
    }

    return this;
}

void STACK_destructor(STACK_STR_p this) {
    free(this->data_array);
    free(this);
}

void STACK_push(STACK_STR_p this, unsigned int data) {
    if (this->pointer_index < this->array_size) {
        this->data_array[this->pointer_index] = data;
        this->pointer_index++;
//        printf("stack elements: %d\n", this->pointer_index);
//        printf("stack size: %d\n", this->array_size);
    } else {
        puts("Error: cannot push more elements onto stack, stack is full");
        exit(1);
    }
}

unsigned int STACK_pop(STACK_STR_p this) {
    this->pointer_index--;

    if (this->pointer_index > this->array_size) { //in case pointer_index was decremented below 0 and is now 0xFFFFFFFF
        puts("Error: cannot pop more elements out of stack, stack is empty");
        exit(1);
    } else {
        return this->data_array[this->pointer_index];
    }
}

unsigned int STACK_peek(STACK_STR_p this) {
    return this->data_array[this->pointer_index];
}
