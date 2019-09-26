#include "malloc.h"
#include <stdio.h>

#define DEBUG 1
static Header base;             // empty list to get started
static Header *freep = NULL;    // start of free list

/*
The function morecore obtains storage from the operating system. The details of how it does this vary from system to system. Since asking the system for memory is a comparatively expensive operation, we don’t want to do that on every call to malloc, so morecore requests at least NALLOC units
*/
#define NALLOC  1024    // minimum #units to request

/*
The UNIX system call sbrk(n) returns a pointer to n more bytes of storage. sbrk returns −1 if there was no space, even though NULL would have been a better design. The −1 must be cast to char * so it can be compared with the return value.
*/
// morecore: ask system for more memory
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;

    if(nu < NALLOC)
        nu = NALLOC;
#if DEBUG
    printf("apply new memory from system, units %u, size %lu bytes\n", nu, nu * sizeof(Header));
#endif

    cp = sbrk(nu * sizeof(Header));
    if(cp == (char *) -1)   // no space at all
        return NULL;
#if DEBUG
    printf("success apply new memory from address %p\n", (void *)cp);
#endif

    up = (Header *)cp;
    up->s.size = nu;
    free_t((void *)(up+1));
    print_list();
    return freep;
}

// malloc: general-purpose storage allocator
void *malloc_t(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
#if DEBUG
    printf("apply nunits %u\n", nunits);
#endif
    if((prevp = freep) == NULL) {   // no free list yet
        base.s.next = freep = prevp = &base;
        base.s.size = 0;
#if DEBUG
        printf("base addr %p\n", (void *)&base);
#endif
    }

    for(p = prevp->s.next; ; prevp = p, p = p->s.next) {
        if(p->s.size >= nunits) {   // big enough
            if(p->s.size == nunits) // exactly 
                prevp->s.next= p->s.next;
            else {      // allocate tail end
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
#if DEBUG
            printf("malloc in addr %p, return addr %p\n", (void *)(p), (void *)(p+1));
            print_list();
#endif
            return (void *)(p+1);
        }
        if(p == freep)      // wrapped around free list
            if((p = morecore(nunits)) == NULL)
                return NULL;     // none left
    }
    // we should never come heare
    return NULL;
}

/*
free itself is the last thing. It scans the free list, starting at freep, looking for the place to insert the free block. This is either between two existing blocks or at one end of the list
*/
// free: put block ap in free list
void free_t(void *ap)
{
    Header *bp, *p;

    bp = (Header *)ap - 1;      // point to block header
    for(p = freep; !(bp > p && bp < p->s.next); p = p->s.next)  // if bp is between p and p->next, stop loop
        if(p >= p->s.next && (bp > p || bp < p->s.next))
            break;  // freed block at start or end of arena

    if(bp + bp->s.size == p->s.next) {     // join to upper nbr
        bp->s.size += p->s.next->s.size;
        bp->s.next = p->s.next->s.next;
#if DEBUG
        printf("join upper\n");
#endif
    } else
        bp->s.next = p->s.next;

    if(p + p->s.size == bp) {       // join to lower nbr
        p->s.size += bp->s.size;
        p->s.next = bp;
#if DEBUG
        printf("join lower\n");
#endif
    } else
        p->s.next = bp;

    freep = p;
}

void print_list(void)
{
    Header *p;
    int i = 0;
    for(p = freep, i = 0; ; p = p->s.next, i++) {
        printf("element[%04d], addr %p, data addr %p, next ele addr %p, size 0x%x\n", i, (void *)p, (void *)(p+1), p->s.next, p->s.size);  
        if(freep == p->s.next)
            break;
    }
}
