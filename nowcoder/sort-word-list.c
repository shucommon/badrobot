#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char **a, int i, int j)
{
    char *tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void q_sort(char **a, int left, int right)
{
    int cnt = left;
    int it;
    
    if(left >= right)
        return;

    for(it = left + 1; it <= right; it++)
    {
        if(strcmp(a[left], a[it]) > 0)
        {
            swap(a, ++cnt, it);
        }        
    }
    swap(a, cnt, left); 
    q_sort(a, left, cnt - 1);
    q_sort(a, cnt + 1, right);
}

int main()
{
    int n;
    scanf("%d", &n);
    
    char **a = (char**)malloc(sizeof(char*)*n);
    char b[100];
    char **p = a;
    for(int i = 0; i < n; i++, p++)
    {
        scanf("%s", b);
        int len = strlen(b);
        *p = (char*)malloc(sizeof(char) * len);
        strcpy(*p, b);
    }

    q_sort(a, 0, n - 1);

    for(int i = 0; i < n; i++, a++)
    {
        printf("%s\n", *a);
    }

    return 0;
}
