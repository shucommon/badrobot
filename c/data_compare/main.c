#include <stdio.h>

int cacul_crc(char*buf, int len)
{
    int sum = 0, i = 0;
    for(i = 0; i < len; i++)
    {
        sum += buf[i];
    }
    return sum;
}

int main()
{
    unsigned int sum[4] = {0} ;
    unsigned int hdata, hlen = 0;
    
    FILE *fp = fopen("header.txt", "r");
    if(fp == NULL)
    {
        printf("error opening header.txt\n");
        return -1;
    }

    fscanf(fp, "%x", &hdata); 
    printf("test %d\n", 0+0xff);
    while(!feof(fp)) 
    {
        sum[hlen%4] += hdata;
        //printf("sum[%d]=%x\n", hlen%4, sum[hlen%4] );
        sum[hlen%4] = (sum[hlen%4] >> 8) + (sum[hlen%4] & 0xff);
        //printf("sum[%d]=%x\n", hlen%4, sum[hlen%4]);
        sum[hlen%4] += (sum[hlen%4] >> 8);
        //printf("sum[%d]=%x\n", hlen%4, sum[hlen%4]);
        printf("%02x: %02x sum(%x) ", (hlen+1), hdata, sum[hlen%4]);
        if(hlen == 44) 
            break;
        hlen++;
        if(hlen % 10 == 0)
            printf("\n");
        fscanf(fp, "%x", &hdata); 
    }
    //printf("\nhlen = %d,sum[0-3] %02x-%02x-%02x-%02x \n", hlen, sum[0], sum[1], sum[2], sum[3]);
    printf("\nhlen = %d,sum[0-3] %02x-%02x-%02x-%02x \n", hlen, ~sum[0], ~sum[1], ~sum[2], ~sum[3]);

    return 0;
}
