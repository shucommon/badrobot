#include <stdio.h>
#include <stdlib.h>
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

void swap_mac_addr(void * pkt_ptr)
{
    uint32_t w;
    uint16_t s;

    /* assuming an IP/IPV6 pkt i.e. L2 header is 2 byte aligned, 4 byte non-aligned */
    s = *(uint16_t *)pkt_ptr;
    w = *(uint32_t *)(pkt_ptr + 2);
    *(uint16_t *)pkt_ptr = *(uint16_t *)(pkt_ptr + 6);
    *(uint32_t *)(pkt_ptr + 2) = *(uint32_t *)(pkt_ptr + 8);
    *(uint16_t *)(pkt_ptr + 6) = s;
    *(uint32_t *)(pkt_ptr + 8) = w;
}

int main()
{
    char *s = (char *)malloc(sizeof(char) * 12);
    for(int i = 0; i < 12; i++)
        s[i] = i + 1;
    for(int i = 0; i < 12; i++)
        printf("%x ", s[i]);
    swap_mac_addr((void *)s);
    for(int i = 0; i < 12; i++)
        printf("%x ", s[i]);

    return 0;
}
