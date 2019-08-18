#include "stack.h"

stack * stack_create(int len)
{
    stack *s = (stack *)malloc(sizeof(stack));
    if(s == NULL) {
        printf("malloc new stack failed\n");
        return NULL;
    }

    s->data = (datatype *)malloc(sizeof(datatype) * len);
    if(s->data == NULL) {
        printf("malloc new data space failed\n");
        return NULL;
    }
    s->maxlen = len;
    s->top = -1;

    return s;
}

int stack_empty(stack *s)
{
    return (s->top == -1);
}

void stack_clear(stack *s)
{
    s->top = -1;
}

int stack_full(stack *s)
{
    return (s->top == s->maxlen - 1);
}

int stack_push(stack *s, datatype data)
{
    if(stack_full(s)) {
        printf("stack full\n");
        return -1;
    }

    s->data[s->top + 1] = data;
    s->top++;

    return -1;
}

datatype stack_pop(stack *s)
{
    return s->data[s->top--];
}

datatype stack_top(stack *s)
{
    return s->data[s->top];
}

int stack_destory(stack *s)
{
    free(s->data);
    s->data = NULL;
    free(s);
    s = NULL;
}
