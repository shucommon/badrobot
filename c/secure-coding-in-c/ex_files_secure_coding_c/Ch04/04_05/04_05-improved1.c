#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char filename[] = "access.txt";
	FILE *fp;
	char pin[6],input[6];
	char *r;
	int fr;
	
	/* obtain PIN */
	fp = fopen(filename,"r");
	if( fp==NULL )
	{
		fprintf(stderr,"Unable to open %s\n",filename);
		exit(1);
	}
	r = fgets(pin,6,fp);
	if( r==NULL )
	{
		fprintf(stderr,"Bad file read\n");
		exit(1);
	}
	fr = fclose(fp);
	if( fr!=0 )
	{
		perror("Error closing file: ");
	}

	/* fetch input */
	printf("Enter your PIN: ");
	r = fgets(input,6,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Invalid input\n");
		exit(1);
	}

	/* validate */
	if( strcmp(input,pin)==0 )
	{
		puts("Access granted");
	}
	else
	{
		puts("Intruder alert!");
	}

	return(0);
}
