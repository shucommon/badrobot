#include <stdio.h>
   
int max(int m, int n)
{
    return m > n ? m:n;
}
  
int main()
{
    int N, m, i, j;
    while(scanf("%d %d", &N, &m) != EOF)
    {
        int v[60] = {0};
        int w[60] = {0};
        int q[60] = {0};
        int sum[3200] = {0};
        for(i=1; i<=m; i++)
        {
            scanf("%d %d %d", &v[i], &w[i], &q[i]);
        }
/*
        for(i=1; i<=m; i++)
        {
            for(j=N/10; j>=1; j--)
            {
                if((v[i]+v[q[i]])/10 <= j)
                    sum[j] = max(sum[j-v[i]/10]+v[i]*w[i], sum[j]);
                else
                    sum[j] = 0;
            }
        }
*/
        for(i=1; i<=m; i++)
        {
            for(j=N/10; j>=1; j--)
            {
                if((v[i])/10 <= j)
                    sum[j] = max(sum[j-v[i]/10]+v[i]*w[i], sum[j]);
                else
                    sum[j] = 0;
            }
        }
        printf("%d\n", sum[N/10]);


        int tmp = 0;
        for(int i = m; i > 0; i--) {
            for(int j = N/10; j > 0; j--) {
                if(sum[j] == sum[j-v[i]/10]+v[i]*w[i]) {
                    printf("v[%d] %d w[%d] %d q[%d] %d choosed\n", i, v[i], i, w[i], i, q[i]);
                    j -= v[i]/10;
                    tmp += v[i]*w[i];
                    break;
                }
            }
        }
        printf("sum %d\n", tmp);
    }
    return 0;
}
