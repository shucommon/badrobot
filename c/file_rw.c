#include <stdio.h>
#include <string.h>

void read_file()
{
	FILE *pf;
	pf = fopen("./testfile", "r");
	char buff[32];
	int steer = 0;
	int associ = 0;
	while(EOF != fscanf(pf, "%s", buff))
	{
		if(0 == strcmp(buff, "STEERED"))
			fscanf(pf, "%d", &steer);
		if(0 == strcmp(buff, "ASSOCIATED"))
			fscanf(pf, "%d", &associ);
	}
	fclose(pf);
	printf("steer %d, associa %d\n", steer, associ);
}

int main(void)
{
	FILE * fp;
	fp = fopen("./testfile", "w");
	fprintf(fp, "STEERED\t\t%d\n", 10);
	fprintf(fp, "ASSOCIATED\t%d\n", 20);
	fclose(fp);

	read_file();

	return 0;
}	
