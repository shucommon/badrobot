/*
10.70.44.68~255.254.255.0       // wrong
1.0.0.1~255.0.0.0
192.168.0.2~255.255.255.0
19..0.~255.255.255.0            // wrong
192.168.0.2~255.255.255.255     // wrong
1.0.0.1~0.0.0.0                 // wrong

A类地址1.0.0.0~126.255.255.255;
B类地址128.0.0.0~191.255.255.255;
C类地址192.0.0.0~223.255.255.255;
D类地址224.0.0.0~239.255.255.255；
E类地址240.0.0.0~255.255.255.255
私网IP范围是：
10.0.0.0～10.255.255.255
172.16.0.0～172.31.255.255
192.168.0.0～192.168.255.255
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int prase_ip_mask(char *a, int *ip)
{
    char *s = a, *e = a;
    int index = 0;
    while(*e != '\0') {
        if(*e == '.' || *e == '~') {
            *e = '\0';
            if(strlen(s) == 0)
                return 0;
            ip[index] = atoi(s);
            if(ip[index] < 0 || ip[index] > 255)
                return 0;
            s = e+1;
            index++;
        }
        e++;
        a++;
    }
    if(strlen(s) == 0)
        return 0;
    ip[index] = atoi(s);
    if(ip[index] < 0 || ip[index] > 255 || index != 7)
        return 0;

    int tmp = (ip[4] << 24) | (ip[5] << 16) | (ip[6] << 8) | ip[7];
    if(tmp == 0 || tmp == 0xffffffff)
        return 0;
    if( ((~tmp + 1) & ~tmp & 0xffffffff) != 0)
        return 0;

    return 1;
}

int main()
{
    char a[50];
    int ip[8];
    int err = 0, A=0, B=0, C=0, D=0, E=0, private=0;
    while(scanf("%s", a) != EOF)
    {
        if(prase_ip_mask(a, ip) == 0)
        {
            err++;
            continue;
        }
        
        if( 1 <= ip[0] && ip[0] <= 126) A++;
        if( 128 <= ip[0] && ip[0] <= 191) B++;
        if( 192 <= ip[0] && ip[0] <= 223) C++;
        if( 224 <= ip[0] && ip[0] <= 239) D++;
        if( 240 <= ip[0]) E++;
        if( 10 == ip[0] || (172 == ip[0] && 16 <= ip[1] && ip[1] <=31) || (192 == ip[0] && 168 == ip[1])) private++;
    }
    printf("%d %d %d %d %d %d %d\n", A, B, C, D, E, err, private);
    return 0;
}
