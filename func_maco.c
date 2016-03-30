#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%d%d%d%d%d%d%d%d"
#define BYTE_TO_BINARY(byte) \
	(byte & 0x80 ? 1 : 0), \
	(byte & 0x40 ? 1 : 0), \
	(byte & 0x20 ? 1 : 0), \
	(byte & 0x10 ? 1 : 0), \
	(byte & 0x08 ? 1 : 0), \
	(byte & 0x04 ? 1 : 0), \
	(byte & 0x02 ? 1 : 0), \
	(byte & 0x01 ? 1 : 0)  \

void myFunc(void)
{
	printf("%s:\n", __func__);
}

typedef enum 
{
	VAL1 = 10,
	VAL2,
	VAL3 = 100,
	VAL4
}val;

int main(int argc, char* argv[])
{
	unsigned char id;
	id = 1-2;
	printf("force val3 - val4 = %u\n", id);
	printf("force val3 - val4 = %u\n",(unsigned char)( -2));
	printf("val3 - val4 = %x\n", VAL3 - VAL4);
	printf("leading text " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(0xaa));
	myFunc();
	printf("test" "%d\n", 1);
	printf("val1: %d, 2: %d, 3: %d\n", VAL1, VAL2, VAL3);
	return 0;
}
