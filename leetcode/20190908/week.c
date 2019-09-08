/*
给你一个日期，请你设计一个算法来判断它是对应一周中的哪一天。

输入为三个整数：day、month 和 year，分别表示日、月、年。

您返回的结果必须是这几个值中的一个 {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}。
*/
#include <stdio.h>

int CalDay(int a, int b, int c)
{
    int month[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
                      {0,31,29,31,30,31,30,31,31,30,31,30,31}};
    int leap = ((0==a%4 && 0!=a%100)||(0==a%400));
    for(int i=1; i<b; i++)
        c += month[leap][i];
    return c;
}

char * dayOfTheWeek(int day, int month, int year){
    int D,W;
    D=CalDay(year,month,day);
    W = year-1+(int)((year-1)/4)-(int)((year-1)/100)+(int)((year-1)/400)+D;
    static char weekday[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return weekday[W%7];
}

int main()
{
    return 0;
}
