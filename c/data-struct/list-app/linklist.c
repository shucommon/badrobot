#include "linklist.h"

linklist* link_create()
{
    linklist *h;
    h = (linklist *)malloc(sizeof(linklist));
    if(h == NULL) {
        printf("malloc new linklist failed\n");
        return NULL;
    }
    h->data = 0;
    h->next = NULL;
    return h;
}

int list_insert_tail(linklist *h, int data)
{
    linklist *p = h;
    while(p->next)
        p = p->next;
    p->next = link_create();
    if(p->next)
        p->next->data = data;
    else
        return -1;
    return 0;
}

void make_round(linklist *h)
{
    linklist *p = h;
    while(p->next)
        p = p->next;
    p->next = h;
}

void list_show(linklist *h)
{
    linklist *p = h;
    if(p == NULL) {
        printf("link is NULL\n");
        return;
    }
    while(p) {
        printf("list(%p) data %d\n", (void *)p, p->data);
        p = p->next;
        if(p == h)
            break;
    }
}

int joseph(linklist *h, int k, int m)
{
    linklist *p = h, *q;
    int i = 1;

    if(k == 1 && m == 1) {
        while(p) {
            q = p;
            p = p->next;
            if(p == h)
                break;
        }
    }

    while(i < k){
        q = p;
        p = p->next;
        i++;
    }
    while(p) {
        i = 1;
        while(i < m) {
            q = p;
            p = p->next;
            i++;
        }
        q->next = p->next;
        printf("out %d\n", p->data);
        free(p);
        p = q->next;
        if(p == q) {
            printf("out %d\n", p->data);
            break;
        }
    }

    return 0;
}

