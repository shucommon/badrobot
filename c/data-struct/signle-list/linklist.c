#include "linklist.h"

linklist* link_create()
{
    linklist *h = (linklist *)malloc(sizeof(linklist));
    if(h == NULL) {
        printf("malloc new linklist failed\n");
        return NULL;
    }
    h->data = 0;
    h->next = NULL;
    return h;
}

linklist* link_create2()
{
    linklist *H, *p, *n;
    datatype data;

    H = (linklist *)malloc(sizeof(linklist));
    if(H == NULL) {
        printf("malloc new linklist failed\n");
        return NULL;
    }
    H->data = 0;
    H->next = NULL;

    p = H;
    while(1) {
        printf("please input a positive value (-1 exit):\n");
        scanf("%d", &data);
        if(data == -1)
            break;

        n = (linklist *)malloc(sizeof(linklist)); 
        if(n == NULL) {
            printf("malloc new linklist failed\n");
            return NULL;
        }
        n->data = data;
        n->next = NULL;
        p->next = n;
        p = n;
    }

    return H;
}

void list_show(linklist *h)
{
    if(h == NULL) {
        printf("link is NULL\n");
        return;
    }
    while(h->next) {
        printf("list(%p) data %d\n", (void *)h->next, h->next->data);
        h = h->next;
    }
}

int list_head_insert(linklist *h, datatype data)
{
    linklist *n = (linklist *)malloc(sizeof(linklist));
    if(n == NULL) {
        printf("link is NULL\n");
        return -1;
    }
    n->data = data;
    n->next = h->next; 
    h->next = n;
    return 0;
}

linklist* list_get(linklist *h, int pos)
{
    if(pos < 0)
        return NULL;

    int i = -1;
    while(h->next && i < pos){
        h = h->next;
        i++;
    }
    if(i == pos)
        return h;
    return NULL;
}

linklist* list_locate(linklist *h, datatype data)
{
    while(h->next) {
        if(h->next->data == data)
            return h->next;
        h = h->next;
    }
    return NULL;
}

int list_insert(linklist *h, int pos, datatype data)
{
    linklist *pre, *n;
    if(pos == 0) {
        pre = h;
    } else {
        pre = list_get(h, pos - 1);
    }
    if(pre == NULL)
        return -1;
    n = link_create();
    if(n == NULL)
        return -1;
    n->data = data;
    n->next = pre->next;
    pre->next = n;
    return 0;
}

int list_delete(linklist *h, int pos)
{
    linklist *pre, *n;
    if(pos == 0) {
        pre = h;
    } else {
        pre = list_get(h, pos - 1);
    }
    if(pre == NULL || pre->next == NULL)
        return -1;

    n = pre->next;   
    pre->next = n->next;
    free(n);
    n = NULL;
    return 0;
}

void list_reverse(linklist *h)
{
    linklist *p = h->next, *q;
    h->next = NULL;

    while(p) {
        q = p->next;
        p->next = h->next; 
        h->next = p;
        p = q;
    }
}

int list_insert_ordered(linklist *h, datatype data)
{
    linklist *p = (linklist *)malloc(sizeof(linklist));
    if(p == NULL) {
        printf("malloc new link node failed\n");
        return -1;
    }
    
    p->data = data;

    linklist *q = h;
    while(q->next && q->next->data < data) {
        q = q->next;
    }
    p->next = q->next;
    q->next = p;
    return 0;
}

void list_sort(linklist *h)
{
    linklist *p, *q, *r;
    p = h->next;
    h->next = NULL;

    while(p) {
        q = p->next;

        r = h;
        while(r->next && r->next->data < p->data)
            r = r->next;
        p->next = r->next;
        r->next = p;

        p = q;
    }
}
