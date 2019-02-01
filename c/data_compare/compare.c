#include <stdio.h>

int main()
{
    FILE *rx = fopen("rx2.txt", "r");
    FILE *tx = fopen("tx2.txt", "r");
    FILE *header = fopen("header.txt", "r");

    int rdata, tdata, hdata;

    fscanf( rx, "%x", &rdata);
    fscanf( tx, "%x", &tdata);
    fscanf( header, "%x", &hdata);
    
    int rlen = 0, tlen = 0, hlen = 0;
    
    printf("rdata:\n"); 
    while(!feof(rx))
    {
        rlen++;
        fscanf( rx, "%x", &rdata);
        printf("%04x : %02x ", rlen, rdata); 
        if(rlen % 10 == 0)
            printf("\n");
    }
    printf("\nrx length %d\n", rlen);

    printf("tdata:\n"); 
    while(!feof(tx))
    {
        tlen++;
        fscanf( tx, "%x", &tdata);
        printf("%04x : %02x ", tlen, tdata); 
        if(tlen % 10 == 0)
            printf("\n");
    }
    printf("\ntx length %d\n", tlen);

    printf("header:\n"); 
    while(!feof(header))
    {
        hlen++;
        printf("%04x : %02x ", hlen, hdata); 
        fscanf( header, "%x", &hdata);
        if(hlen % 10 == 0)
            printf("\n");
    }
    printf("\nheader length %d\n", hlen);

    rewind(tx);
    rewind(rx);

    fscanf( rx, "%x", &rdata);
    fscanf( tx, "%x", &tdata);
    
    rlen = 0;
    tlen = 0;
    
    while(!feof(rx) && !feof(tx))
    {
        rlen++;
        if( rdata != tdata)
            printf("%04x:rdata = hex:%02x | dec:%03d -- tdata = hex:%02x | dex:%0xd\n", rlen, rdata, rdata, tdata, tdata); 
        fscanf( rx, "%x", &rdata);
        fscanf( tx, "%x", &tdata);
    }
    fclose(tx);
    fclose(rx);
}
