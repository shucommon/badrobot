#include <stdio.h>
#include <string.h>

int main()
{
    char *a = "你好";
    printf("%s\n", a);

    for(int i = 0; i < strlen(a); i++)
    {
        printf("c: %c d: %d x: %x\n", a[i], (unsigned char)a[i], (unsigned char)a[i]);
    }

    a = "汉字";
    printf("%s\n", a);

    for(int i = 0; i < strlen(a); i++)
    {
        printf("c: %c d: %d x: %x\n", a[i], (unsigned char)a[i], (unsigned char)a[i]);
    }

    char data_utf8[]={0xE6,0xB1,0x89,0xE5,0xAD,0x97};
    printf("%s\n", data_utf8);

    return 0;
}
