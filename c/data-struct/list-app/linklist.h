#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} linklist;

linklist* link_create();
int list_insert_tail(linklist *h, int data);
int list_delete(linklist *h, int pos);
void list_show(linklist *h);
void make_round(linklist *h);
int joseph(linklist *h, int k, int m);

#endif
