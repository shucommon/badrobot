#include "dlist.h"


dlistnode * dlist_create()
{
    dlistnode *h, *r;
    int data;
    h = (dlistnode *)malloc(sizeof(dlistnode));
    if(h == NULL) {
        printf("malloc new dlistnode failed\n");
        return NULL;
    }

    h->prior = h;
    h->next = h;

    r = h;
    while(1) {
        printf("please input int(-1 exit):\n");
        scanf("%d", &data);
        if(data == -1)
            break;
        
        dlistnode *p = (dlistnode *)malloc(sizeof(dlistnode));
        if(p == NULL)
            break;

        p->data = data;

        p->prior = r;
        p->next = r->next;
        r->next->prior = p;
        r->next = p; 

        r = p;
    }

    return h;
}

void dlist_show(dlistnode *H)
{
    dlistnode *p;
    p = H->next;
    printf("head(%p)\n", (void *)H);
    while(p != H) {
        printf("node(%p)(prior %p next %p) data %d\n", (void *)p, (void*)p->prior, (void*)p->next, p->data);
        p = p->next;
    }
}

dlistnode * dlist_get(dlistnode *h, int pos)
{
    int i = -1;
    dlistnode *p = h;

    if(pos < 0) {
        printf("pos < 0, invalidted\n");
        return NULL;
    }
    while(i < pos) {
        p = p->next;
        i++;
        if(p == h) {
            printf("not found\n");
            return NULL;
        }
    }
    return p;
}

int dlist_insert(dlistnode *h, int pos, int data)
{
    dlistnode *p, *q;

    p = dlist_get(h, pos);
    if(p == NULL)
        return -1;

    q = (dlistnode *)malloc(sizeof(dlistnode));
    if(q == NULL) {
        printf("malloc new node failed\n");
        return -1;
    }

    q->data = data;
    q->prior = p->prior;
    q->next = p;
    p->prior->next = q;
    p->prior = q;

    return 0;
}

int dlist_delete(dlistnode *h, int pos)
{
    dlistnode *p;
    p = dlist_get(h, pos);
    if(p == NULL) {
        printf("not found\n");
        return -1;
    }

    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
    p = NULL;    
    return 0;
}
