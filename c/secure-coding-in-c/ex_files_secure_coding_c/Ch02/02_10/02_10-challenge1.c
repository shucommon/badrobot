#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buffer;
	int index;
	char ch;
	const char filename[] = "challenge.txt";
	FILE *fp;

	buffer = (char *)malloc( sizeof(char) * 32 );
    if(buffer == NULL) {
        printf("failed to malloc memory\n");
        return 1;
    }

	printf("Type some text: ");
	index = 0;
	while( (ch=getchar()) )
	{
		*(buffer+index) = ch;
		index++;
        if(index > 31)
            break;
		if( ch=='\n')
			break;
	}
	/* cap the string */
	*(buffer+index) = '\0';

	fp = fopen(filename,"w");
	fwrite(buffer,1,index,fp);
	fclose(fp);
	printf("%s created\n",filename);

	return(0);
}

