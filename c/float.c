#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * float format:
 *   bit31 bit30-bit23 bit22-bit0
 *   sign  exponent    fraction
 *   value = (-1)^sign * 2^(e-127) * (1 + [i<0-22>]bit.i * 2^(i-23)) 
 */
 
typedef union {
    float a;
    unsigned char b[4];
} float2char;

// low memory with low byte is little endian
// low memory with high byte is big endian
typedef union {
    int a;
    unsigned char b[4];
} endian;

int main(int argc, char** argv)
{
    if(argc != 2) {
        printf("Usage: ./a.out a_float_number\n");
        return -1;
    }

    float2char tmp;
    tmp.a=atof(argv[1]);
    printf("input %f\n", tmp.a);
    
    endian ed;
    ed.a = 0x11223344;
    printf("mem info %x %x %x %x\n", ed.b[0],ed.b[1],ed.b[2],ed.b[3]);
    printf("add info %p %p %p %p\n", &ed.b[0],&ed.b[1],&ed.b[2],&ed.b[3]);

    if(ed.b[0] == 0x44) {
        printf("little endian, float mem info %x %x %x %x\n", tmp.b[3],tmp.b[2],tmp.b[1],tmp.b[0]);
    } else {
        printf("big endian, float mem info %x %x %x %x\n", tmp.b[0],tmp.b[1],tmp.b[2],tmp.b[3]);
    }

    return 0;
}
