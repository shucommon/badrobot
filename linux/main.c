#include <stdio.h>
#include "list.h"

int main()
{
    HLIST_HEAD(hh);
    struct hlist_node hn;
    INIT_HLIST_NODE(&hn);
    hh.first = &hn;
    hn.pprev = &hh.first;

    printf("hh addr %p\n", (void *)&hh);
    printf("hh->first addr %p\n", (void *)hh.first);
    printf("hn addr %p\n", (void *)&hn);
    printf("hn->pprev addr %p\n", (void *)hn.pprev);

    struct hlist_node hn1;
    INIT_HLIST_NODE(&hn1);
    hlist_add_head(&hn1, &hh);
    printf("hh addr %p\n", (void *)&hh);
    printf("hh->first addr %p\n", (void *)hh.first);
    printf("hn1 addr %p\n", (void *)&hn1);
    printf("hn1->pprev addr %p\n", (void *)hn1.pprev);

    return 0;
}
