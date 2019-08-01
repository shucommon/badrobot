#include "linklist.h"

int main()
{
    linklist *h = link_create();
    h->data = 1;
    int n;
    scanf("%d", &n);
    for(int i = 2; i <= n; i++) {
        if(list_insert_tail(h, i) != 0)
            printf("insert failed\n");
    }
    make_round(h);
    list_show(h);

    joseph(h, 3, 4);
    //joseph(h, 1, 1);

    return 0;
}
