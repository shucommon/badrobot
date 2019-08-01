#include "dlist.h"

int main()
{
    int pos, data;
    dlistnode *h, *p;

    h = dlist_create();
    dlist_show(h);

/*
    while(1) {
        printf("input pos:\n");
        scanf("%d", &pos);
        p = dlist_get(h, pos);
        if(p) {
            printf("found node (%p) %d\n", p, p->data);
        }
    }
    while(1) {
        printf("insert node pos data:\n");
        scanf("%d %d", &pos, &data);
        int ret = dlist_insert(h, pos, data);
        if(ret == 0) {
            printf("insert success:\n"); 
            dlist_show(h);
        }
    }
*/
    printf("delete 0\n");
    dlist_delete(h, 0);
    dlist_show(h);
    printf("\n");

    printf("delete 1\n");
    dlist_delete(h, 1);
    dlist_show(h);
    printf("\n");

    printf("delete 2\n");
    dlist_delete(h, 2);
    dlist_show(h);
    printf("\n");
    return 0;
}
