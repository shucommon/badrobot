#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int k;
} elem;

typedef struct {
    elem m;
    elem sub[3];
    int sub_cnt;
} shop_list;

void print_content(int cnt, shop_list **pele)
{
    printf("cnt %d\n", cnt);
    for(int i = 0; i < cnt; i++)
    {
        printf("main val %d - k %d, sub_cnt %d\n", pele[i]->m.val, pele[i]->m.k, pele[i]->sub_cnt);
        for(int j = 0; j < pele[i]->sub_cnt; j++)
            printf("  sub val %d, sub k %d\n", pele[i]->sub[j].val, pele[i]->sub[j].k); 
    }
}

int cacl(int N, int cnt, shop_list **pele)
{
    int total = 0;
    for(int i = 0; i < cnt; i++)
    {
        pele[i]->total = pele[i]->m.val * pele[i]->m.k;
        for(int j = 0; j < pele[i]->sub_cnt; j++)
            pele[i] 
    }
}

int main()
{
    int N, m;
    int v, p, q;
    int cnt = 0;
    scanf("%d %d", &N, &m);

    shop_list **pele = (shop_list **)malloc(sizeof(shop_list *) * m);
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d %d", &v, &p, &q);
        if(q == 0) {
            pele[cnt] = (shop_list *)malloc(sizeof(shop_list));
            pele[cnt]->m.val = v;
            pele[cnt]->m.k= p;
            pele[cnt]->sub_cnt = 0;
            cnt++;
        } else {
            int sc = pele[q-1]->sub_cnt;
            pele[q-1]->sub[sc].val = v;
            pele[q-1]->sub[sc].k = p;
            pele[q-1]->sub_cnt++;
        }
    }

    //print_content(cnt, pele);
    printf("%d\n", cacl(N, cnt, pele));

    return 0;
}
    
