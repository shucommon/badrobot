#include<stdio.h>

int main()
{
	char str[18] = "12 34:56:ab:cd:ef";
	int num = 0;
	int en[6];
	
	num = sscanf(str, "%02x %02x:%02x:%02x:%02x:%02x", 
				&en[0], &en[1], &en[2], &en[3], &en[4], &en[5]);
	for(int i = 0; i < 6; i++)
	{
		printf("en[%d] = %x\n", i, en[i]);
	}
	return 0;
}
