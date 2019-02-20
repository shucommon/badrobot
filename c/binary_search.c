#include<stdio.h>
#include<stdlib.h>

int main(int argc, char** argv)
{
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int cnt = sizeof(array)/sizeof(int);
	int index=cnt/2;
	int target;
	int start = 0, end = cnt - 1;
	int i = 0;
	if(argc < 2)
	{
		printf("please pass at least one parmeter\n");
		return -1;
	}
    printf("cnt = %d, initial index %d\n", cnt, index);
	target = atoi(argv[1]);

	while(start <= end)
	{
		i++;
		printf("pre index %d\n", index);
		if(array[index] == target)
		{
			printf("found %d, index %d, search %d times\n", target, index, i);
			return 0;
		}
		else if(array[index] > target)
		{
			end = index - 1;
		}
		else
		{
			start = index + 1;
		}
		index = (start + end)/2;
		printf("post index %d\n", index);
	}
	printf("not found\n");

	return 0;
}
