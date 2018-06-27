#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* #define TEST_CALLBACK */
#define TEST_ALIGNMENT

typedef void (*ts_prtf)(void *);

void test_print(void * i)
{
	switch(*((int*)i))
	{
	case 1:
		printf("hello\n");
		break;
	case 2:
		printf("byebye\n");
		break;
	default:
		printf("?\n");
	}
}
void test_callback(ts_prtf ts, void * i)
{
	ts(i);
	return;
}

typedef struct
{
	char data1;
	int data2;
	unsigned short data3;
	char data4;
} __attribute__((aligned(2))) test_alignment;

int main(int argc, char**grgc)
{
#ifdef TEST_CALLBACK
	int i = 0;
	for(i = 0; i < 3; i++)
	{
		test_callback(test_print, (void*)&i);
	}
#endif

#ifdef TEST_ALIGNMENT
	printf("size: %d \n", sizeof(test_alignment));
#endif

    char * str = "/dev/ddnva";
    int fd = open(str,  O_RDWR);
    if(fd < 0)
        printf("error open ddnva\n");
    else
    {
        printf("open ddnva\n");
        close(fd);
    }
    printf("sizeof(unsigned short) = %u\n", sizeof(unsigned short));
	return 0;
}
