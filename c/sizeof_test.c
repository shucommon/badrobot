#include <stdio.h>

struct probe
{
	int a;
	int b;
	char c[4];
};
struct node
{
	int a;
	char b;
};
struct netlink_event
{
	int type;
	int index;

	union
	{
		struct probe bs_probe;
		struct node bs_node;
	} data;
};

struct test
{
	unsigned short a;
	int b;
	unsigned short c;
	unsigned char d;
	unsigned char e; 
	unsigned char f;
};

int main(int argc, char* argv[])
{
	typedef struct qca
	{
		char a;
		int b;
	} qc;
	
	qc qc1;
	qc* qc2;
	qc qc3[2];
	int len1 = sizeof qc1;
	int len2 = sizeof *qc2;
	int len3 = sizeof(qc);
	int len4 = sizeof(qc3);
	int len5 = sizeof(qc3[0]);
	printf("sizeof qc1 %d, sizeof qc2 %d,sizeof(qc) %d\n", len1, len2, len3); 
	printf("sizeof qc3 %d, qc3[0] %d\n", len4, len5);
	printf("sizeof netlink_event %d\n", sizeof(struct netlink_event));
	struct test ts;
	printf("sizofo ts %d\n", sizeof(ts));
	return 0;
}
