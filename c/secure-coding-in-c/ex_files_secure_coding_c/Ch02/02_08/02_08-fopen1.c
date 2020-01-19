#include <stdio.h>

int main()
{
	FILE *fp;
	int r;

	fp = fopen("test.txt","r");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to open that file!\n");
		return(1);
	}
	printf("File opened\n");

	r = fclose(fp);
	if( r != 0 )
	{
		fprintf(stderr,"Unable to close file\n");
		/* process EOF and errno value here */
		return(1);
	}

	return(0);
}
