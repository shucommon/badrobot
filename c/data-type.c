#include <stdint.h>         // int8_t ... 
#include <stdio.h>
#include <inttypes.h>       // PRId32 etc
#include <limit.h>          // defines a set of constants delimiting the ranges of the different integer data types for the particular machine

int main()
{
    int8_t a;
    int16_t b;
    int32_t c;
    int64_t d;
    
    a = 127;        // 0x7f
    b = 32767;      // 0x7fff
    c = 2147483647; // 0x7fffffff
    d = 9223372036854775807; // 0x7fffffffffffffff 

    printf("a = %" PRId8 ", b = %" PRId16 ", c = %" PRId32 ", d = %" PRId64 "\n", a, b, c, d); 
    a +=1;
    b +=1;
    c +=1;
    d +=1;
    printf("a = %" PRId8 ", b = %" PRId16 ", c = %" PRId32 ", d = %" PRId64 "\n", a, b, c, d); 
   
    printf("INT8_MAX = %" PRId8 ", INT16_MAX = %" PRId16 ", INT32_MAX = %" PRId32 ", INT64_MAX = %" PRId64 "\n", INT8_MAX, INT16_MAX, INT32_MAX, INT64_MAX); 
    
    return 0;
}
