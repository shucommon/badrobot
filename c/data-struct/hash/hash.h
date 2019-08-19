/*
H(key)       hp
        --------------       ---------------
  0     | first node |------>| data | next |
        --------------       ---------------
  1     |            |
        --------------       ---------------       ---------------
  2     |            |------>| data | next |------>| data | next |
        --------------       ---------------       ---------------
  3     |            |
        --------------

  m : hash table length
  p : key % p = index  seems p is not necessary
      if delete p, then index = key % h->length
*/

#ifndef _HASH_H_
#define _HASH_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef int datatype_el;
typedef struct listnode
{
    datatype_el data;
    struct listnode *next;
} list_node;

typedef list_node datatype;
typedef struct hashtbl {
    datatype **h;
    int length;
    int p; // key % p = index
} hash_tbl;

void init_hash(hash_tbl **hp, int m);
void create_hash(hash_tbl *hp, datatype_el *a, int len);
list_node *hash_search(hash_tbl *hp, int key);
void hash_show(hash_tbl *hp, int hash_val);
int * get_random_arr(int len);

#endif
