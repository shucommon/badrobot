#include <stdio.h>
void trans(char *a)
{
	int i = 0;
	printf("********************\n");
	for(i = 0; i < 18; i++)
	{
		printf("char = %c, addr = %p\n", *a, (void*)a);
		a++;
	}


}
int main()
{
	char wlan[10][6] = {"abcdef", "123456", "ABCDEF"}; 
	int i = 0;

	for(i = 0; i < 18; i++)
	{ 
		printf("char = %c, addr = %p\n", *(*wlan+i), (void*)(*wlan+i));
	}
	trans((char*)wlan);
	return 0;
}
