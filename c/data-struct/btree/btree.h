#ifndef _BTREE_H_
#define _BTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char datatype;
typedef struct btreenode {
    datatype data;
    struct btreenode *left;
    struct btreenode *right;
} btree_node;

typedef struct list_node {
    btree_node *node;
    struct list_node *next;
} list;

btree_node * create_btree(void);
void create_btree_new(btree_node **t);
void pre_order_btree(btree_node *root, int d);
void in_order_btree(btree_node *root);
void post_order_btree(btree_node *root);
void level_order_btree(btree_node *root);

#endif
