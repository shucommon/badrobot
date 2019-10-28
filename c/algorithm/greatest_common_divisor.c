#include <stdio.h>
/*
Greatest Common Divisor
最大公约数的求解方法
*/

/*
辗转相除法也叫欧几里得算法，是一种非常古老的求解两个数的最大公约数的算法。其基于的原理：两个正整数a和b（a > b），它们的最大公约数gcd等于a除以b的余数r和b之间的最大公约数。比如，10和25的最大公约数5等于25除以10的余数5和10的最大公约数；再比如51和21的最大公约数3等于51除以21的余数9和21的最大公约数，而9和21的最大公约数为3。根据上面的原理，辗转相除法的算法流程可以如下：
步骤1：计算a与b的余数r。
步骤2：如果r为0，则返回gcd = b。否则，转到步骤3。
步骤3：使用b的值更新a的值，使用余数r更新b的值，转到步骤1
*/

long gcd1(long a, long b)
{
    // don't need test a > b, if a < b, after 1 interator, it become a > b
    return (a % b == 0 ? b : gcd1(b, a % b));
}

/*
更相减损术原理
更相减损术出自《九章算术》，其原理很简单：两个正整数a和b（a > b），它们的最大公约数等于a-b的差值c和较小数b的最大公约数。依次递归下去，直到两个数相等。这相等两个数的值就是所求最大公约数。
*/
long gcd2(long a, long b)
{
    // don't need test a > b, if a < b, after 1 interator, it become a > b
    return (a == b ? a : (a > b ? gcd2(a - b, b): gcd2(b - a, a)));
}


int main()
{
    long a, b;
    while(scanf("%ld %ld", &a, &b) != EOF) {
        if(a == 0 || b == 0)
            break;
        long ret = gcd1(a, b); 
        printf("gcd1: %ld and %ld gcd %ld\n", a, b, ret);
        ret = gcd2(a, b); 
        printf("gcd2: %ld and %ld gcd %ld\n", a, b, ret);
    }
    return 0;
}

