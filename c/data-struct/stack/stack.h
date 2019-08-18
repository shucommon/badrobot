#ifndef _STACK_H_
#define _STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct {
    datatype *data;
    int maxlen;
    int top;
} stack;

stack * stack_create(int len);
int stack_empty(stack *s);
void stack_clear(stack *s);
int stack_full(stack *s);
int stack_push(stack *s, datatype data);
datatype stack_pop(stack *s);
datatype stack_top(stack *s);
int stack_destory(stack *s);

#endif
