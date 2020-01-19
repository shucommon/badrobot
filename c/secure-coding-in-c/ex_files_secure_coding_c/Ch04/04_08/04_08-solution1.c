#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6

int main()
{
	char code[SIZE];
	char suffix[] = "new";
	char *r,*code_new;
	int a;

	/* obtain input */
	printf("Enter your secret code: ");
	r = fgets(code,SIZE,stdin);
	/* verify */
	if( r==NULL )
	{
		fprintf(stderr,"Inavlid input\n");
		exit(1);
	}

	/* remove newline from input */
	for( a=0; a<SIZE; a++)
	{
		if( code[a]=='\n')
		{
			code[a]='\0';
			break;
		}
	}

	/* confirm code is 5 characters */
	if( strlen(code) != 5 )
	{
		puts("Code must be 5 characters long");
		exit(1);
	}

	/* allocate storage for new code */
	code_new = (char *)malloc( strlen(code) + strlen(suffix) + 1);
	if( code_new==NULL )
	{
		fprintf(stderr,"Unable to allocate memory\n");
		exit(1);
	}
	strcpy(code_new,code);
	strcat(code_new,suffix);

	printf("Your new secret code is: %s\n",code_new);
	/* zero out code */
	for( a=0; a<SIZE; a++)
	{
		code[a] = '\0';
	}
	/* zero out new code */
	for( a=0; a<strlen(code_new); a++ )
	{
		*(code_new+a) = '\0';
	}

	return(0);
}
