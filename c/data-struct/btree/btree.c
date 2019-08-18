#include "btree.h"


btree_node * create_btree(void)
{
    char in;
    btree_node *root = NULL;
    
    scanf("%c", &in);
    if(in == '#')
        return root;

    root = (btree_node *)malloc(sizeof(btree_node));
    if(root == NULL) {
        perror("malloc");
        exit(1);
    }
    root->data = in;
    root->left = create_btree();
    root->right = create_btree();

    return root;
}

void create_btree_new(btree_node **t)
{
    char in;
    scanf("%c", &in);
    if(in == '#') {
        *t = NULL;
        return;
    }

    *t = (btree_node *)malloc(sizeof(btree_node));
    if(*t == NULL) {
        perror("malloc");
        exit(1);
    }

    (*t)->data = in;
    create_btree_new(&(*t)->left);
    create_btree_new(&(*t)->right);
}

void pre_order_btree(btree_node *root, int d)
{
    if(root) {
        printf("addr 0x%p - data %c level %d\n", (void *)root, root->data, d);
        pre_order_btree(root->left, d+1);
        pre_order_btree(root->right, d+1);
    }
}

void in_order_btree(btree_node *root)
{
    if(root) {
        in_order_btree(root->left);
        printf("addr 0x%p - data %c\n", (void *)root, root->data);
        in_order_btree(root->right);
    }
}
void post_order_btree(btree_node *root)
{
    if(root) {
        post_order_btree(root->left);
        post_order_btree(root->right);
        printf("addr 0x%p - data %c\n", (void *)root, root->data);
    }
}

void level_order_btree(btree_node *root)
{
    if(root == NULL)
        return;

    list *p1;
    list *p2;
    p1 = p2 = (list *)malloc(sizeof(list));
    p1->node = root;
    p1->next = NULL;
    printf("addr %p data %c\n", (void *)p1->node, p1->node->data);

    while(p1) {
        if(p1->node->left) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->node = p1->node->left;
            p2 = p2->next;
            p2->next = NULL;
            printf("addr %p data %c\n", (void *)p2->node, p2->node->data);
        }
        if(p1->node->right) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->node = p1->node->right;
            p2 = p2->next;
            p2->next = NULL;
            printf("addr %p data %c\n", (void *)p2->node, p2->node->data);
        }
        p1 = p1->next;
    }
}
