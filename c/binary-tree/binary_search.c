#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree {
    int data;
    char c;
    struct binary_tree *left;
    struct binary_tree *right;
} bt;

typedef struct list_bt {
    bt *ele;
    struct list_bt *next;
} list;

void pre_order_traverse(bt *root)
{
    if(root == NULL)
        return;
    printf("%d c %c\n", root->data, root->c);
    pre_order_traverse(root->left);
    pre_order_traverse(root->right);
}

void in_order_traverse(bt *root)
{
    if(root == NULL)
        return;
    in_order_traverse(root->left);
    printf("%d c %c\n", root->data, root->c);
    in_order_traverse(root->right);
}

void post_order_traverse(bt *root)
{
    if(root == NULL)
        return;
    post_order_traverse(root->left);
    post_order_traverse(root->right);
    printf("%d c %c\n", root->data, root->c);
}

void in_deep_order(bt *root)
{
    list *ls;
    if(root != NULL) {
        ls = (list *)malloc(sizeof(list));
        ls->ele = root;
        ls->next = NULL;
        printf("%d c %c\n", ls->ele->data, ls->ele->c);
    } else
        return;

    list *p1 = ls;
    list *p2 = ls;
    while(p1 != NULL) {
        if(p1->ele->left != NULL) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->ele = p1->ele->left;
            p2 = p2->next;
            p2->next = NULL;
            printf("%d c %c\n", p2->ele->data, p2->ele->c);
        }
        if(p1->ele->right != NULL) {
            p2->next = (list *)malloc(sizeof(list));
            p2->next->ele = p1->ele->right;
            p2 = p2->next;
            p2->next = NULL;
            printf("%d c %c\n", p2->ele->data, p2->ele->c);
        }
        p1 = p1->next;
    }
/*
    p1 = ls;
    while(p1 != NULL) {
        printf("%d c %c\n", p1->ele->data, p1->ele->c);
        p1 = p1->next;
    }
*/
}

/*
         a
      b     c
    d   e  f g
   h i j
abdh##i##ej###cf##g##
*/
bt * pre_order_creat_bt()
{
    char input;
    fflush(stdin);
    scanf("%c", &input);
    if(input == '#')
        return NULL;

    bt *root = (bt *)malloc(sizeof(bt));
    root->c = input;
    root->left = pre_order_creat_bt();
    root->right = pre_order_creat_bt();
    return root;
}

int main()
{
    bt *root = pre_order_creat_bt();
    printf("pre print:\n");
    pre_order_traverse(root);

    printf("in print:\n");
    in_order_traverse(root);

    printf("post print:\n");
    post_order_traverse(root);

    printf("in deepth print:\n");
    in_deep_order(root);

    return 0;
}
