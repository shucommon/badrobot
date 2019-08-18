/*
         a
      b     e
       c      f
      d      g
           h   k
*/

#include "btree.h"

int main()
{
    btree_node *root = create_btree();

    printf("pre order:\n");
    pre_order_btree(root, 1);
    printf("in order:\n");
    in_order_btree(root);
    printf("post order:\n");
    post_order_btree(root);
    printf("level order:\n");
    level_order_btree(root);

/*
    btree_node *root1;
    create_btree_new(&root1);

    printf("pre order:\n");
    pre_order_btree(root1);
    printf("in order:\n");
    in_order_btree(root1);
    printf("post order:\n");
    post_order_btree(root1);
 */

    return 0;
}
