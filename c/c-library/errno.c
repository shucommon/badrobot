#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <math.h>

/*
The library has functions and variables designed to make it easy for your program to report informative error messages in the customary format about the failure of a library call.
The functions strerror and perror give you the standard error message for a given error code;
the variable program_invocation_short_name gives you convenient access to the name of the program that encountered the error.

The function strerror is declared in string.h.
The function perror is declared in stdio.h.

Function: char * strerror (int errnum)
Function: char * strerror_r (int errnum, char *buf, size_t n)   //  it returns a private copy for the thread, This might be either some permanent global data or a message string in the user supplied buffer starting at buf with the length of n bytes.
Function: void perror (const char *message) //This function prints an error message to the stream stderr;

*/

//extern int errno ;

int main () {
    FILE *fp;
    
    fp = fopen("file.txt", "r");
    if( fp == NULL ) {
       fprintf(stderr, "Value of errno: %d\n", errno);
       fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    } else {
       fclose(fp);
    }
    
    // demain error
    double val;
    errno = 0;
    val = sqrt(-10);
    
    if(errno == EDOM) {
       printf("Invalid value \n");
    } else {
       printf("Valid value\n");
    }
    printf("%f\n", val);
    
    errno = 0;
    val = sqrt(10);
    
    if(errno == EDOM) {
       printf("Invalid value\n");
    } else {
       printf("Valid value\n");
    }
   
   
    // ERANGE
    double x;
    double value;
    
    x = 2.000000;
    value = log(x);
    
    if( errno == ERANGE ) {
       printf("Log(%f) is out of range\n", x);
    } else {
       printf("Log(%f) = %f\n", x, value);
    }
    
    x = 1.000000;
    value = log(x);
    
    if( errno == ERANGE ) {
       printf("Log(%f) is out of range\n", x);
    } else {
       printf("Log(%f) = %f\n", x, value);
    }
    
    x = 0.000000;
    value = log(x);
    
    if( errno == ERANGE ) {
       printf("Log(%f) is out of range\n", x);
    } else {
       printf("Log(%f) = %f\n", x, value);
    }
    
    return(0);
}
