#include <stdio.h>
#include <stdlib.h>

typedef struct lst {
    int data;
    struct lst *next;
} list;

void list_sort(list *h)
{
    list *p = h->next, *q;
    h->next = NULL;

    while(p) {
        q = p; 
        p = p->next;

        list *t = h;
        while(t->next && (t->next->data < q->data)) {
            t = t->next;
        }
        q->next = t->next;
        t->next = q;
    }
}

void show(list *h)
{
    while(h->next) {
        printf("data %d\n", h->next->data);
        h = h->next;
    }
}

void insert(list *h, int data)
{
    list *n = (list*)malloc(sizeof(list)); 
    n->data = data;
    n->next = NULL;
    while(h->next != NULL) {
        h = h->next;
    }
    h->next = n;
}

int main()
{
    list *h = (list*)malloc(sizeof(list));
    h->next = NULL;
    insert(h, 20);
    insert(h, 10);
    insert(h, 30);
    insert(h, 80);
    insert(h, 50);
    insert(h, 40);
    insert(h, 60);
    insert(h, 55);
    insert(h, 70);
    printf("original:\n");
    show(h);

    list_sort(h);
    printf("sorted:\n");
    show(h);
    
    return 0;
}
