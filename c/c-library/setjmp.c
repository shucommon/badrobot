/*
The setjmp.h header defines the macro setjmp(), one function longjmp(), and one variable type jmp_buf, for bypassing the normal function call and return discipline.
*/

/*
The C library macro int setjmp(jmp_buf environment), saves the current environment into the variable environment for later use by the function longjmp(). If this macro returns directly from the macro invocation, it returns zero but if it returns from a longjmp() function call, then it returns the value passed to longjmp as a second argument.
environment − This is the object of type jmp_buf where the environment information is stored.
*/

/*
In many situations, you may want to jump to a location that is very far away from the current function. Sometimes, the destination is even not in the same function. For example, when a signal occurs, the program logic may require the control flow be sent to a very special function after the signal is handled. In this case, some addition mechanism is required to perform this type of non-local gotos. This is the job of header file setjmp.h and functions setjmp() and longjmp().

To perform non-local gotos, you need to do the following:

Include the header file setjmp.h
You have to use two functions: setjmp() for setting a return point and longjmp() to perform a goto.
Declare a variable of type jmp_buf. This is called a jump buffer.
Here is how to do the job:
Declare a variable of type jmp_buf
jmp_buf JumpBuffer;
This jump buffer is used to store the ``environment'' of a return point in your program.
Mark a ``return'' point using function setjmp(). This function has only one argument of type jmp_buf. Then, the current state of program execution at that point is saved.
jmp_buf JumpBuffer;

setjmp(JumpBuffer);
The above saves the current state of program execution at that point to the jump buffer JumpBuffer.
Later on, in some other functions (or even in the same function), you can use longjmp() to jump back to the marked return point. longjmp() takes two arguments. The first is a jump buffer and the second is a non-zero integer.
jmp_buf JumpBuffer;

longjmp(JumpBuffer, 1);
In this case, longjmp() sends the control back to the place where the jump buffer JumpBuffer receives its most recent information.

*/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

void jmpfunction(jmp_buf env_buf) {
    longjmp(env_buf, 1);
}

int main () {
    int val;
    jmp_buf env_buffer;

    /* save calling environment for longjmp */
    val = setjmp( env_buffer );

    if( val != 0 ) {
      printf("Returned from a longjmp() with value = %d\n", val);
      exit(0);
    }

    printf("Jump function call\n");
    jmpfunction( env_buffer );

    return(0);
}

/*
jmp_buf jumpbuffer;
main()
{
    setjmp(jumpbuffer); <---------+
    a();                          |
}                                 |
a()                               |
{                                 |
    b();                          |
}                                 |
b()                               |
{                                 |
    c();                          |
}                                 |
c()                               |
{                                 |
    longjmp(jumpbuffer, 1); ------+
}
*/

