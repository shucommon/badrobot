#include <stdio.h>

int main()
{
	const char filename[] = "test.txt";
	const char data[] = "123456789\n";
	FILE *fp;
	int r;

	fp = fopen(filename,"w");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to create %s\n",filename);
		return(1);
	}

	r = fwrite(data,1,10,fp);
	if( r != 10 )
	{
		fprintf(stderr,"Unable to write %d bytes to %s\n",r,filename);
		fclose(fp);
		return(1);
	}
	printf("Wrote %d bytes to %s\n",r,filename);

	r = fclose(fp);
	if( r != 0 )
	{
		fprintf(stderr,"Unable to close file\n");
		/* process EOF and errno value here */
		return(1);
	}

	return(0);
}
