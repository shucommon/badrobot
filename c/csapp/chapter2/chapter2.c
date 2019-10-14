#include <stdio.h>
#include <stdint.h>

/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y)
{
    unsigned sum = x + y;
    return sum >= x;
}

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y)
{
    int sum = x+y;
    int neg_over = (x < 0 && y < 0 && sum >= 0);
    int pos_over = (x > 0 && y > 0 && sum < 0);
    return !neg_over && !pos_over;
}

/* Determine whether arguments can be subtracted without overflow */
/* WARNING: This code is buggy. */
int tsub_ok(int x, int y)
{
    if(y == INT32_MIN) {
        if( x < 0)
            return 0;
        else
            return 1;
    }
    return tadd_ok(x, -y);
}

/* Determine whether arguments can be multiplied without overflow */
int tmult_ok(int x, int y)
{
    int p = x*y;
    /* Either x is zero, or dividing p by x gives y */
    return !x || p/x == y;
}

/* For the case where data type int has 32 bits, devise a version of tmult_ok that uses the 64-bit precision of data type int64_t, without using division. */
/* Determine whether arguments can be multiplied without overflow */
int tmult_ok_64(int x, int y)
{
    /* With 64 bits, we can perform the multiplication without overflowing. We then test whether casting the product to 32 bits changes the value */
    /* Compute product without overflow */
    int64_t pll = (int64_t) x * y;
    /* See if casting to int preserves value */
    return pll == (int)pll;
}

/*
Write a function div16 that returns the value x/16 for integer argument x. Your function should not use division, modulus, multiplication, any conditionals (if or ?:), any comparison operators (e.g., <, >, or ==), or any loops. You may assume that data type int is 32 bits long and uses a two’s-complement representation, and that right shifts are performed arithmetically.
The only challenge here is to compute the bias without any testing or conditional operations. We use the trick that the expression x >> 31 generates a word with all ones if x is negative, and all zeros otherwise. By masking off the appropriate bits, we get the desired bias value.
*/
int div16(int x) {
    /* Compute bias to be either 0 (x >= 0) or 15 (x < 0) */
    int bias = (x >> 31) & 0xF;
    return (x + bias) >> 4;
}

int main()
{
    return 0;
}
