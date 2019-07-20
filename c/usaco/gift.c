/*
ID: qianggu1 
LANG: C
TASK: gift1 
*/

/*
5
dave
laura
owen
vick
amr
dave
200 3
laura
owen
vick
*/

#include <stdio.h>
#include <stdlib.h>

int calu(char *a)
{
    int rt = 1;
    while(*a) {
        rt *= (*a - 'A' + 1);
        a++;
    }
    rt %= 47;
    return rt;
}

int main () {
    FILE *fin = fopen("ride.in", "r");
    FILE *fout = fopen("ride.out", "w");
    char a[8], b[8];
    fscanf (fin, "%s", a);
    fscanf (fin, "%s", b);

    if(calu(a) == calu(b))
        fprintf (fout, "%s\n", "GO");
    else
        fprintf (fout, "%s\n", "STAY");

    return 0;
}
