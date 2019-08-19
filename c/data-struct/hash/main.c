#include "hash.h"

int main()
{
    hash_tbl *hp;
    int m, key;
    char ch;
    list_node *ret;

    int len = 15;
    datatype_el *a = get_random_arr(len);
    // len = 11;
    //datatype_el a[] = {23, 34, 14, 38, 46, 16, 68, 15, 7, 31, 26};

    // get hash table size m according to array size
    m = (int)ceil(len/0.75);
    // init hash table space
    init_hash(&hp, m);
    // create hash table
    create_hash(hp, a, len);
    // hash search
    while(1) {
        printf("please input key:");
        scanf("%d", &key);
        ret = hash_search(hp, key);
        if(ret == NULL)
            printf("not found!\n");
        else
            printf("found item(%p) %d : %d\n", (void*)ret, key, ret->data); 
        printf("continue ? (Y/y)");
        while(getchar() != '\n');
        scanf("%c", &ch);
        if(ch == 'y' || ch == 'Y')
            continue;
        break;
    }

    return 0;
}
