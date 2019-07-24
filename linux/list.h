/*
 *        tables            
 *       +-------------+    hlist_node
 *       | hlist_head -+--->+-------+    hlist_node   
 *     0 |             |<-+ | next  |--->+-------+    hlist_node
 *       |-------------|  | |       |<-- | next  |--->+-------+
 *       |             |  | +-------+  | |       |<-- | next==|
 *     1 |             |  +-| pprev |  | +-------+  | | NULL  |
 *       |-------------|    +-------+  +-| pprev |  | +-------+
 *       |             |                 +-------+  +-| pprev |
 *     2 |             |                              +-------+
 *       +-------------+
 *     pprev point to the 'next' element address of previous node 
 *
 */

#include "def.h"

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static inline void INIT_HLIST_NODE(struct hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

static inline int hlist_unhashed(const struct hlist_node *h)
{
    return !h->pprev;
}

static inline int hlist_empty(const struct hlist_head *h)
{
    return !h->first;
}

static inline void __hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next)
        next->pprev = pprev;
}

static inline void hlist_del(struct hlist_node *n)
{
    __hlist_del(n);
    n->next = LIST_POISON1;
    n->pprev = LIST_POISON2;
}

static inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    struct hlist_node *first = h->first;
    n->next = first;
    if (first)
        first->pprev = &n->next;
    h->first = n;
    n->pprev = &h->first;
}

/* next must be != NULL */
static inline void hlist_add_before(struct hlist_node *n,
                    struct hlist_node *next)
{
    n->pprev = next->pprev;
    n->next = next;
    next->pprev = &n->next;
    *(next->pprev) = n;
}

/* next is the new node */
static inline void hlist_add_after(struct hlist_node *n,
                    struct hlist_node *next)
{
    next->next = n->next;
    n->next = next;
    next->pprev = &n->next;
    if(next->next)
        next->next->pprev = &next->next;
}

/*
 * Move a list from one list head to another. Fixup the pprev
 * reference of the first entry if it exists.
 */
static inline void hlist_move_list(struct hlist_head *old,
                   struct hlist_head *new)
{
    new->first = old->first;
    if(new->first)
        new->first->pprev = &new->first;
    old->first = NULL;
}


