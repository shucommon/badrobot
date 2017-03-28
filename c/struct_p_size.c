#include <stdio.h>
#include <stdlib.h>

typedef struct BlNetDev
{
	char v1;
	int v2;
	float v3;
	char v4[1];
}	BlNetDev;

typedef struct IfRuntimeData
{
	int v1;
	char v2;
	float v3;
}	IfRuntimeData;

int main(int argc, char* argv[])
{
	BlNetDev *blNetDev = calloc(sizeof(BlNetDev), 1);
	
	IfRuntimeData *pRuntime = (IfRuntimeData *)((void*)blNetDev->v4);
	if(pRuntime == NULL)
	{
		printf("pRuntime is NULL\n");	
	}

	printf("blNetDev point value %d\n",(int)blNetDev); 
	printf("pRuntime point value %d\n",(int)pRuntime);

	return 0;
}
