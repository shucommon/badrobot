#include "hash.h"

// m = 15, ret 13
int fun(int m)
{
    int i;
    for(; m > 1; m--) {
        for(i = 2; i < m; i++)
            if(m % i == 0)
                break;
        if(i >= m)
            return m;
    }
    return -1;
}

// caller have the duty to free return arr
int * get_random_arr(int len)
{
    int *arr = (int *)malloc(sizeof(int) * len);

    time_t t;
    /* Intializes random number generator */
    srand((unsigned) time(&t));
    for(int i = 0; i < len; i++)
        arr[i] = rand() % 100 + 1;

    return arr;
}


void init_hash(hash_tbl **hp, int m)
{
    *hp = (hash_tbl *)malloc(sizeof(hash_tbl));
    if(NULL == *hp) {
        perror("malloc");
        exit(-1);
    }
    (*hp)->length = m;
    int p = fun(m);
    if(p == -1)
        exit(-1);
    (*hp)->p = p;
    
    (*hp)->h = (datatype **)malloc(sizeof(datatype *) * (*hp)->length);
    if((*hp)->h == NULL) {
        perror("malloc");
        exit(-1);
    }
    for(int i = 0; i < (*hp)->length; i++)
        (*hp)->h[i] = NULL;
}

// len : array len
void create_hash(hash_tbl *hp, datatype_el *a, int len)
{
    int hash_val, i;
    list_node *new;

    for(int i = 0; i < len; i++) {
        hash_val = a[i] % hp->p;
        new = (list_node *)malloc(sizeof(list_node));
        if(NULL == new) {
            perror("malloc");
            exit(-1);
        }
        new->data = a[i];
        new->next = hp->h[hash_val];
        hp->h[hash_val] = new;

        hash_show(hp, hash_val);
        sleep(1);
    }
}

list_node *hash_search(hash_tbl *hp, int key)
{
    int hash_val;
    list_node *p;

    hash_val = key % hp->p;
    for(p = hp->h[hash_val]; p != NULL; p = p->next) {
        if(p->data == key)
            return p;
    }
    return NULL;
}

void hash_show(hash_tbl *hp, int hash_val)
{
    list_node *p;
    for(int i = 0; i < hp->length; i++) {
        printf("hp->h[%02d]:", i);
        for(p = hp->h[i]; p != NULL; p = p->next)
            printf("----->(%p)%d", (void *)p, p->data);
        if(i == hash_val)
            printf("<---inserting\n");
        else
            printf("\n");
    }
    printf("****************************************\n");
}

