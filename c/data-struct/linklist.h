#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node {
    datatype data;
    struct node *next;
} linklist;

// assume header doesn't contain data
linklist* link_create();
linklist* link_create2();
int list_head_insert(linklist *h, datatype data);
int list_insert(linklist *h, int pos, datatype data);
int list_insert_ordered(linklist *h, datatype data);
void list_sort(linklist *h);
int list_delete(linklist *h, int pos);
void list_reverse(linklist *h);
linklist* list_get(linklist *h, int pos);
linklist* list_locate(linklist *h, datatype data);
void list_show(linklist *h);

#endif
