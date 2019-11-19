/*
The math.h header defines various mathematical functions and one macro. All the functions available in this library take double as an argument and return double as the result.
*/


#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main () {
    double x, y, ret, val;

    x = 0.9;
    val = 180.0 / PI;

    /*
    Returns the arc cosine of x in radians.
    x − This is the floating point value in the interval [-1,+1].
    double acos(double x)
    */
    ret = acos(x) * val;
    printf("The arc cosine of %lf is %lf degrees\n", x, ret);

    /*
    double asin(double x)
    Returns the arc sine of x in radians.
    x − This is the floating point value in the interval [-1,+1].
    */
    ret = asin(x) * val;
    printf("The arc sine of %lf is %lf degrees\n", x, ret);

    /*
    3	double atan(double x)
    Returns the arc tangent of x in radians.
    x − This is the floating point value.
    This function returns the principal arc tangent of x, in the interval [-pi/2,+pi/2] radians.
    */
    x = 1.0;
    val = 180.0 / PI;
    ret = atan (x) * val;
    printf("The arc tangent of %lf is %lf degrees\n", x, ret);

    /*
    4	double atan2(double y, double x)
    Returns the arc tangent in radians of y/x based on the signs of both values to determine the correct quadrant.
    x − This is the floating point value representing an x-coordinate.
    y − This is the floating point value representing a y-coordinate.
    This function returns the principal arc tangent of y/x, in the interval [-pi,+pi] radians.
    */
    x = -7.0;
    y = 7.0;
    val = 180.0 / PI;

    ret = atan2 (y,x) * val;
    printf("The arc tangent of x = %lf, y = %lf ", x, y);
    printf("is %lf degrees\n", ret);

    /*
    5	double cos(double x)
    Returns the cosine of a radian angle x.
    x − This is the floating point value representing an angle expressed in radians.
    */
    x = 60.0;
    val = PI / 180.0;
    ret = cos( x*val );
    printf("The cosine of %lf is %lf degrees\n", x, ret);

    x = 90.0;
    val = PI / 180.0;
    ret = cos( x*val );
    printf("The cosine of %lf is %lf degrees\n", x, ret);

    /*
    6	double cosh(double x)
    Returns the hyperbolic cosine of x.
    */
    x = 0.5;
    printf("The hyperbolic cosine of %lf is %lf\n", x, cosh(x));

    x = 1.0;
    printf("The hyperbolic cosine of %lf is %lf\n", x, cosh(x));

    x = 1.5;
    printf("The hyperbolic cosine of %lf is %lf\n", x, cosh(x));

    /*
    7	double sin(double x)
    Returns the sine of a radian angle x.
    */
    x = 45.0;
    val = PI / 180;
    ret = sin(x*val);
    printf("The sine of %lf is %lf degrees\n", x, ret);

    /*
    8	double sinh(double x)
    Returns the hyperbolic sine of x.
    */
    x = 0.5;
    ret = sinh(x);
    printf("The hyperbolic sine of %lf is %lf degrees\n", x, ret);

    /*
    9	double tanh(double x)
    Returns the hyperbolic tangent of x.
    */
    x = 0.5;
    ret = tanh(x);
    printf("The hyperbolic tangent of %lf is %lf degrees\n", x, ret);

    /*
    10	double exp(double x)
    Returns the value of e raised to the xth power.
    */
    x = 0;
    printf("The exponential value of %lf is %lf\n", x, exp(x));
    printf("The exponential value of %lf is %lf\n", x+1, exp(x+1));
    printf("The exponential value of %lf is %lf\n", x+2, exp(x+2));

    /*
    11	double frexp(double x, int *exponent)
    The returned value is the mantissa and the integer pointed to by exponent is the exponent. The resultant value is x = mantissa * 2 ^ exponent.
        x − This is the floating point value to be computed.
        exponent − This is the pointer to an int object where the value of the exponent is to be stored.
        This function returns the normalized fraction. If the argument x is not zero, the normalized fraction is x times a power of two, and its absolute value is always in the range 1/2 (inclusive) to 1 (exclusive). If x is zero, then the normalized fraction is zero and zero is stored in exp.
    */
    double fraction;
    x = 1024;
    int e;
    fraction = frexp(x, &e);
    printf("x = %.2lf = %.2lf * 2^%d\n", x, fraction, e);

    /*
    12	double ldexp(double x, int exponent)
    Returns x multiplied by 2 raised to the power of exponent.
    This function returns x * 2 exp
    */
    int n;
    x = 0.65;
    n = 3;
    ret = ldexp(x ,n);
    printf("%f * 2^%d = %f\n", x, n, ret);

    /*
    13	double log(double x)
    Returns the natural logarithm (base-e logarithm) of x.
    */
    x = 2.7;
    /* finding log(2.7) */
    ret = log(x);
    printf("log(%lf) = %lf\n", x, ret);

    /*
    14	double log10(double x)
    Returns the common logarithm (base-10 logarithm) of x.
    */
    x = 10000;
    /* finding value of log1010000 */
    ret = log10(x);
    printf("log10(%lf) = %lf\n", x, ret);

    /*
    15	double modf(double x, double *integer)
    The returned value is the fraction component (part after the decimal), and sets integer to the integer component.
    */
    double fractpart, intpart;
    x = 8.123456;
    fractpart = modf(x, &intpart);

    printf("Integral part = %lf\n", intpart);
    printf("Fraction Part = %lf \n", fractpart);

    /*
    16	double pow(double x, double y)
    Returns x raised to the power of y.
    */
    printf("Value 8.0 ^ 3 = %lf\n", pow(8.0, 3));
    printf("Value 3.05 ^ 1.98 = %lf\n", pow(3.05, 1.98));

    /*
    17	double sqrt(double x)
    Returns the square root of x.
    */
    printf("Square root of %lf is %lf\n", 4.0, sqrt(4.0) );
    printf("Square root of %lf is %lf\n", 5.0, sqrt(5.0) );

    /*
    18	double ceil(double x)
    Returns the smallest integer value greater than or equal to x.
    */
    float val1, val2, val3, val4;

    val1 = 1.6;
    val2 = 1.2;
    val3 = 2.8;
    val4 = 2.3;

    printf ("value1 = %.1lf\n", ceil(val1));
    printf ("value2 = %.1lf\n", ceil(val2));
    printf ("value3 = %.1lf\n", ceil(val3));
    printf ("value4 = %.1lf\n", ceil(val4));

    /*
    19	double fabs(double x)
    Returns the absolute value of x.
    */
    float a, b;
    a = 1234;
    b = -344;

    printf("The absolute value of %lf is %lf\n", a, fabs(a));
    printf("The absolute value of %lf is %lf\n", b, fabs(b));

    /*
    20	double floor(double x)
    Returns the largest integer value less than or equal to x.
    */
    val1 = 1.6;
    val2 = 1.2;
    val3 = 2.8;
    val4 = 2.3;

    printf("Value1 = %.1lf\n", floor(val1));
    printf("Value2 = %.1lf\n", floor(val2));
    printf("Value3 = %.1lf\n", floor(val3));
    printf("Value4 = %.1lf\n", floor(val4));

    /*
    21	double fmod(double x, double y)
    Returns the remainder of x divided by y.
    */
    int c;
    a = 9.2;
    b = 3.7;
    c = 2;
    printf("Remainder of %f / %d is %lf\n", a, c, fmod(a,c));
    printf("Remainder of %f / %f is %lf\n", a, b, fmod(a,b));

    return(0);
}
