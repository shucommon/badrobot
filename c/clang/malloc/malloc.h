#include <stdio.h>
/*

A block returned by malloc

+--------------------------+-------+-----------+
|points to next free block | size  |           |
+--------------------------+-------+-----------+
                                   ^
                                   |
    address returned to user ------+
*/

typedef long Align; // for alignment to long boundary

union header {  // block header:
    struct {
        union header *next;      // next block if no free list
        unsigned size;          // size of this block
    } s;
    Align x;                    // force alignment of blocks
};
typedef union header Header;

void free_t(void *ap);
void *malloc_t(unsigned nbytes);
void print_list(void);
