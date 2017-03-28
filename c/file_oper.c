#include <stdio.h>

int main(void)
{
	FILE * fp;
	fp = fopen("./testfile", "w");
	fprintf(fp, "this is a test file of file operation");
	fseek(fp, 2, SEEK_SET);
	fputs("at", fp);

	fseek(fp, -1, SEEK_END);
	fputc('a', fp);

	
	
	return 0;
}	
