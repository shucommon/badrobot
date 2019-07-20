/*
ID: qianggu1 
LANG: C
TASK: friday 
*/
#include <stdio.h>
#include <stdlib.h>

// return 0 - 6 -> sunday - saturday 
int calu(int y, int m, int d)
{
    int days[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int leap_year = (((y%4 == 0) && (y%100 != 0)) || (y%400 == 0)) ? 1:0;
    int D = days[m-1] + d;
    D = ((leap_year && m > 2) ? D+1:D);

    int W = y - 1 + (y - 1)/4 - (y-1)/100 + (y-1)/400 + D;
    return W%7;
}

int main () {
    FILE *fin = fopen("friday.in", "r");
    FILE *fout = fopen("friday.out", "w");
    int n;
    fscanf (fin, "%d", &n);

    int start = 1900;
    int days[7] = {0};
    for(int i = 0; i < n; i++)
        for(int j = 1; j <= 12; j++)
            days[calu(start + i, j, 13)]++; 

    fprintf (fout, "%d ", days[6]);
    for(int i = 0; i < 6; i++)
    {
        fprintf (fout, "%d", days[i]);
        if(i < 5)
            fprintf (fout, "%c", ' ');
        else
            fprintf (fout, "%c", '\n');
    }

    return 0;
}
