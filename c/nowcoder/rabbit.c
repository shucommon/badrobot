#include <stdio.h>

/*
有一只兔子，从出生后第3个月起每个月都生一只兔子，小兔子长到第三个月后每个月又生一只兔子，假如兔子都不死，问每个月的兔子总数为多少？
*/

/**
 * 统计出兔子总数。
 * 
 * @param monthCount 第几个月
 * @return 兔子总数
 */
int rabbit(int m)
{
    int one = 1, two = 0, three = 0, total = 0, i=1;
    while(m--) {
        total = one + two + three;
        //printf("month %d, one %d, two %d, three %d, total %d\n",i++, one, two, three, total);
        three += two; 
        two = one;
        one = three;
    }
    return total;
}

int main()
{
    int m;
    while(scanf("%d", &m) != EOF) {
        if(m == 0)
            break;
        printf("month %d : rabbit %d\n", m, rabbit(m));
    }

    return 0;
}
