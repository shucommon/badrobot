#include "stack.h"


int main()
{
    stack *s;
    int n = 10;

    s = stack_create(n);

    stack_push(s, 10);
    stack_push(s, 20);
    stack_push(s, 30);
    stack_push(s, 40);

    while(!stack_empty(s)) {
        printf("%d\n", stack_pop(s));
    }

    return 0;
}
