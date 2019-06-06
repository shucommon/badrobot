#include <stdio.h>

typedef unsigned char * byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    printf("0x");
    for(i = 0; i < len; i++)
        printf("%.2x", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
    show_bytes((byte_pointer) x, sizeof(void *));
}

int main()
{
    int x = 0x12345678;
    float f = 0x1;
    int *p = &x;

    show_int(x);
    show_float(f);
    show_pointer((void*)p);
    printf("p pointer addr %p\n", (void *)p);
    printf("*p pointer addr %p\n", (void *)&p);
    printf("*p val 0x%lx\n",(long)&p);

    return 0;
}
