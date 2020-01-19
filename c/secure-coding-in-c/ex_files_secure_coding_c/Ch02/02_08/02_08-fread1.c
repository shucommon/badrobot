#include <stdio.h>

int main()
{
	const char filename[] = "test.txt";
	char buffer[16];
	int r;
	FILE *fp;

	fp = fopen(filename,"r");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to open %s\n",filename);
		return(1);
	}

	r = fread(buffer,1,16,fp);
	if( r!= 16 )
	{
		if( feof(fp) )
			printf("Read %d bytes from %s\n",r,filename);
		else
		{
			r = ferror(fp);
			printf("Error: ferror() returned %d\n",r);
		}
	}

	r = fclose(fp);
	if( r != 0 )
	{
		fprintf(stderr,"Unable to close file\n");
		/* process EOF and errno value here */
		return(1);
	}

	return(0);
}
