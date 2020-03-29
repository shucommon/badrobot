#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} list_t;

list_t * reverse(list_t *h) {
    if(h == NULL || h->next == NULL)
        return h;

    list_t *tmp = reverse(h->next);
    list_t *node1 = h->next;
    node1->next = h;
    h->next = NULL; 
    return tmp;
}

void p(list_t *h)
{
    while(h) {
        printf("data %d -> ", h->data);
        h = h->next;
    }
}

int main()
{
    list_t *h;
    h = (list_t *)malloc(sizeof(list_t));
    h->data = 5;
    h->next = NULL;
    list_t *it = h;

    for(int i = 0; i < 5; i++) {
        list_t *n = (list_t *)malloc(sizeof(list_t));
        n->data = 4 - i;
        n->next = NULL;
        it->next = n;
        it = n;
        printf("inset data %d\n", n->data);
    }
    p(h);
    h = reverse(h);
    p(h);

    return 0;
}
