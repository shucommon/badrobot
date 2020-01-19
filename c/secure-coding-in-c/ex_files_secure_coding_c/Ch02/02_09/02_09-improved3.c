#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char filename[] = "binary.dat";
	FILE *fp;
	int a,r;

	fp = fopen(filename,"r");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to open %s\n",filename);
		exit(1);
	}

	while(1)
	{
		r = fread(&a,sizeof(int),1,fp);
		if( r != 1 )
		{
			if( feof(fp) )
				break;
			else
				perror("File read error: ");
		}
		printf("%d\n",a);
	}

	r = fclose(fp);
	if( r==EOF )
		perror("File closing error");

	return(0);
}
