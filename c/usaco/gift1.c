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
#include <string.h>
#include <stdlib.h>

int find_index(char **table, char *index, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(strcmp(table[i], index) == 0)
            return i;
    }
    return n;   // indicate wrong
}

int main () {
    FILE *fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    int np, total, div, give, left;
    char **name;
    int *money;
    char tmp[15];

    fscanf (fin, "%d", &np);
    name = (char **)malloc(sizeof(char*) * np);
    money = (int *)malloc(sizeof(int) * np);

    for(int i = 0; i < np; i++)
    {
        fscanf (fin, "%s", tmp);
        name[i] = (char*)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(name[i], tmp);
        money[i] = 0;
    }

    for(int i = 0; i < np; i++)
    {
        fscanf (fin, "%s", tmp);
        int index = find_index(name, tmp, np); 

        fscanf (fin, "%d %d", &total, &div);
        if(div) {
            give = total / div;
            left = total % div;
        } else {
            give = 0;
            left = total;
        }
        money[index] -= (total - left);
            
        for(int j = 0; j < div; j++)
        {
            fscanf (fin, "%s", tmp);
            index = find_index(name, tmp, np); 
            money[index] += give;
        }
    }

    for(int i = 0; i < np; i++)
    {
        fprintf(fout, "%s %d\n", name[i], money[i]);
    }

    return 0;
}
