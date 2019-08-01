#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prior;
    struct node *next;
} dlistnode;

dlistnode * dlist_create();
void dlist_show(dlistnode *H);
dlistnode * dlist_get(dlistnode *h, int pos);
int dlist_insert(dlistnode *h, int pos, int data);
int dlist_delete(dlistnode *h, int pos);

#endif
