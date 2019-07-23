/*
 *        tables
 *       +--------+
 *       |        |    +------+------+    +------+------+
 *     0 |       -+--->|value | next |--->|value | NULL |
 *       |--------|    +------+------+    +------+------+
 *       |        |
 *     1 |       -+---> NULL
 *       |--------|
 *       |        |    +------+------+
 *     2 |       -+--->|value | NULL |
 *       |--------|    +------+------+
 *       |        |    +------+------+    +------+------+    +------+------+
 *     3 |       -+--->|value | next |--->|value | next |--->|value | NULL |
 *       +--------+    +------+------+    +------+------+    +------+------+
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int key_type;
typedef int value_type; 

typedef struct _hash_node {
    key_type key;
    value_type value;
    struct _hash_node *next;  
} hash_node;

typedef struct _hash_table {
    int capacity;   // total capacity
    int size;       // current size
    hash_node **tables;
} hash_table;

// return a proper hash table size for a giving n
int hash_table_kPrime( int n )
{
    static const unsigned long _prime_list [] =
    {
        53ul, 97ul, 193ul, 389ul, 769ul,
        1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
        49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
        1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
        50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
        1610612741ul, 3221225473ul, 4294967291ul
    };
    const int _prime_size = 28;
    for(int i = 0; i < _prime_size; i++)
        if(_prime_list[i] > n)
            return _prime_list[i];  

    return _prime_list[_prime_size - 1];
}

hash_node * creat_new_node(key_type key, value_type value)
{
    hash_node *new_node = (hash_node *)malloc(sizeof(hash_node));
    assert(new_node);
    new_node->key = key;
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

// return index for a given key
key_type hash_func(key_type key, int n)
{
    return key % n;
}

void hash_table_init(hash_table *ht, int n)
{
    assert(ht);
    ht->size = 0;
    ht->capacity = n;
    ht->tables = (hash_node **)malloc(sizeof(hash_node *) * n);
    assert(ht->tables);
    memset((char *)ht->tables, 0, sizeof(hash_node *) * n);
}

int hash_table_insert(hash_table *ht, key_type key, value_type value)
{
    // create new node
    hash_node *new_node = creat_new_node(key, value);

    // if table is full(size >= capacity), enlarger hash table
    if(ht->size >= ht->capacity) {
        hash_table new_ht;
        hash_table_init(&new_ht, hash_table_kPrime(ht->capacity));
        for(int i = 0; i < ht->capacity; i++) {
            if(!ht->tables[i]) {
                continue;
            }
            hash_node *cur = ht->tables[i];
            while(cur) {
                hash_node *next = cur->next;
                key_type index = hash_func(cur->key, new_ht.capacity);
                cur->next = new_ht.tables[index];
                new_ht.tables[index] = cur;
                cur = next;
            }
        }
        free(ht->tables);
        ht->tables = new_ht.tables;
        ht->capacity = new_ht.capacity;
    }

    // insert new node 
    key_type index = hash_func(key, ht->capacity);
    if(!ht->tables[index]) {
        ht->tables[index] = new_node;
    } else {
        hash_node *cur = ht->tables[index];
        while(cur) {
            if(cur->value == value)
                return -1;
            cur = cur->next;
        }

        new_node->next = ht->tables[index];
        ht->tables[index] = new_node;
    }
    ht->size++;
    return 0;
}

hash_node * hash_table_find(hash_table *ht, key_type key)
{
    key_type index = hash_func(key, ht->capacity);
    if(!ht->tables[index])
        return NULL;

    hash_node *node = ht->tables[index];
    while(node) {
        if(node->key == key)
            return node;
        node = node->next;
    }
    return NULL;
}

int hash_table_remove(hash_table *ht, key_type key)
{
    key_type index = hash_func(key, ht->capacity);
    if(!ht->tables[index])
        return -1;

    hash_node *cur = ht->tables[index];
    hash_node *pre = ht->tables[index];
    while(cur) {
        if(cur->key == key) {
            if(cur == pre) {  // first node
                ht->tables[index] = cur->next;
            } else {
                pre->next = cur->next;
            }
            free(cur);
            ht->size--;
            cur = NULL;
            return 0;
        }
        pre = cur;
        cur = cur->next;
    }
    return -1;
}

void destory_hash_table(hash_table *ht)
{
    for(int i = 0; i < ht->capacity; i++) {
        if(!ht->tables[i])
            continue;

        hash_node *cur = ht->tables[i];
        while(cur) {
            hash_node *tmp = cur;
            cur = cur->next;
            free(tmp);
            tmp = NULL;
        }
    }
    free(ht->tables);
    ht->tables = NULL;
    ht->size = 0;
    ht->capacity = 0;
}

void print_hash_table(hash_table *ht)
{
    for(int i = 0; i < ht->capacity; i++) {
        if(!ht->tables[i]) {
            printf("bucket %d is null\n", i);
            continue;
        }

        hash_node *cur = ht->tables[i];
        printf("bucket %d:\n", i);
        while(cur) {
            printf("\t%d-%d", cur->key, cur->value);
            cur = cur->next;
            if(cur)
                printf(" -> ");
            else
                printf("\n");
        }
    }
}

int main()
{
    hash_table ht;
    int n = 16;
    hash_table_init(&ht, n);
    for(int i = 0; i < 32; i++)
        hash_table_insert(&ht, i, i);
    print_hash_table(&ht);

    hash_node *hn = hash_table_find(&ht, 1);
    if(hn)
        printf("%d-%d\n", hn->key, hn->value);
    hn = hash_table_find(&ht, 30);
    if(hn)
        printf("%d-%d\n", hn->key, hn->value);
        
    for(int i = 10; i < 16; i++) {
        hash_table_remove(&ht, i);
    }
    print_hash_table(&ht);

    return 0;
}
