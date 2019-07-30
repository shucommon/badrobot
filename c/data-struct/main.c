#include "linklist.h"

int main()
{
    linklist *H = link_create();
    list_show(H);
    printf("list insert ordered:\n");
    list_insert_ordered(H, 10);
    list_insert_ordered(H, 20);
    list_insert_ordered(H, 50);
    list_insert_ordered(H, 40);
    list_insert_ordered(H, 4);
    list_insert_ordered(H, 25);
    list_show(H);
    printf("\n");

    printf("list insert head 1->2->3\n");
    list_head_insert(H, 1);
    list_head_insert(H, 2);
    list_head_insert(H, 3);
    list_show(H);
    printf("\n");

    printf("insert pos 0 4\n");
    list_insert(H, 0, 4);
    list_show(H);
    printf("\n");

    printf("insert pos 1 5\n");
    list_insert(H, 1, 5);
    list_show(H);
    printf("\n");

    printf("insert pos 5 6\n");
    list_insert(H, 5, 6);
    list_show(H);
    printf("\n");

    printf("list reverse:\n");
    list_reverse(H);
    list_show(H);
    printf("\n");

    printf("list sort\n");
    list_sort(H);
    list_show(H);
    printf("\n");

    printf("delete pos 5\n");
    list_delete(H, 5);
    list_show(H);
    printf("\n");

    printf("delete pos 4\n");
    list_delete(H, 4);
    list_show(H);
    printf("\n");

    printf("delete pos 0\n");
    list_delete(H, 0);
    list_show(H);
    printf("\n");


    return 0;
}
