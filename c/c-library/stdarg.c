/*
The stdarg.h header defines a variable type va_list and three macros which can be used to get the arguments in a function when the number of arguments are not known i.e. variable number of arguments.
A function of variable arguments is defined with the ellipsis (,...) at the end of the parameter list.

va_list
    This is a type suitable for holding information needed by the three macros va_start(), va_arg() and va_end().

Library Macros

1	void va_start(va_list ap, last_arg)
This macro initializes ap variable to be used with the va_arg and va_end macros. The last_arg is the last known fixed argument being passed to the function i.e. the argument before the ellipsis.

2	type va_arg(va_list ap, type)
This macro retrieves the next argument in the parameter list of the function with type type.

3	void va_end(va_list ap)
This macro allows a function with variable arguments which used the va_start macro to return. If va_end is not called before returning from the function, the result is undefined.
*/
#include<stdarg.h>
#include<stdio.h>

int sum(int, ...);

int main(void) {
    printf("Sum of 10, 20 and 30 = %d\n",  sum(3, 10, 20, 30) );
    printf("Sum of 4, 20, 25 and 30 = %d\n",  sum(4, 4, 20, 25, 30) );
    return 0;
}

int sum(int num_args, ...) {
    int val = 0;
    va_list ap;
    int i;

    va_start(ap, num_args);
    for(i = 0; i < num_args; i++) {
        val += va_arg(ap, int);
    }
    va_end(ap);

    return val;
}
