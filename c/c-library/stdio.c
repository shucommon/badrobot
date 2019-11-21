#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>

/*
The stdio.h header defines three variable types, several macros, and various functions for performing input and output.

Library Variables
1	
size_t
This is the unsigned integral type and is the result of the sizeof keyword.
2	
FILE
This is an object type suitable for storing information for a file stream.
3	
fpos_t
This is an object type suitable for storing any position in a file.

Library Macros
1	
NULL
This macro is the value of a null pointer constant.

2	
_IOFBF, _IOLBF and _IONBF
These are the macros which expand to integral constant expressions with distinct values and suitable for the use as third argument to the setvbuf function.

3	
BUFSIZ
This macro is an integer, which represents the size of the buffer used by the setbuf function.

4	
EOF
This macro is a negative integer, which indicates that the end-of-file has been reached.

5	
FOPEN_MAX
This macro is an integer, which represents the maximum number of files that the system can guarantee to be opened simultaneously.

6	
FILENAME_MAX
This macro is an integer, which represents the longest length of a char array suitable for holding the longest possible filename. If the implementation imposes no limit, then this value should be the recommended maximum value.

7	
L_tmpnam
This macro is an integer, which represents the longest length of a char array suitable for holding the longest possible temporary filename created by the tmpnam function.

8	
SEEK_CUR, SEEK_END, and SEEK_SET
These macros are used in the fseek function to locate different positions in a file.

9	
TMP_MAX
This macro is the maximum number of unique filenames that the function tmpnam can generate.

10	
stderr, stdin, and stdout
These macros are pointers to FILE types which correspond to the standard error, standard input, and standard output streams.

*/

/*
Library Functions
1	int fclose(FILE *stream)
Closes the stream. All buffers are flushed.
*/
void fclose_t()
{
    FILE *fp;

    fp = fopen("file.txt", "w");
    fprintf(fp, "%s", "This is tutorialspoint.com");
    fclose(fp);
}
/*
2	void clearerr(FILE *stream)
Clears the end-of-file and error indicators for the given stream.
This should not fail and do not set the external variable errno but in case it detects that its argument is not a valid stream, it must return -1 and set errno to EBADF.
*/
void clearerr_t()
{
    FILE *fp;
    char c;

    fp = fopen("file.txt", "w");

    c = fgetc(fp);
    if( ferror(fp) ) {
        printf("Error in reading from file : file.txt\n");
    }
    clearerr(fp);

    if( ferror(fp) ) {
        printf("Error in reading from file : file.txt\n");
    }
    fclose(fp);
}

/*
3	int feof(FILE *stream)
Tests the end-of-file indicator for the given stream.
*/

void feof_t()
{
   FILE *fp;
   int c;
  
   fp = fopen("file.txt","r");
   if(fp == NULL) {
      perror("Error in opening file");
      return;
   }
   
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);
}

/*
4	int ferror(FILE *stream)
Tests the error indicator for the given stream.
*/
void ferror_t()
{
   FILE *fp;
   char c;

   fp = fopen("file.txt", "w");

   c = fgetc(fp);
   if( ferror(fp) ) {
      printf("Error in reading from file : file.txt\n");
   }
   clearerr(fp);
   
   if( ferror(fp) ) {
      printf("Error in reading from file : file.txt\n");
   }
   fclose(fp);
}

/*
5	int fflush(FILE *stream)
Flushes the output buffer of a stream.
*/
void fflush_t()
{
   char buff[1024];
   
   memset( buff, '\0', sizeof( buff ));
   
   fprintf(stdout, "\nGoing to set full buffering on\n");
   setvbuf(stdout, buff, _IOFBF, 1024);

   fprintf(stdout, "This is tutorialspoint.com\n");
   fprintf(stdout, "This output will go into buff\n");
   fflush( stdout );

   fprintf(stdout, "and this will appear when programm\n");
   fprintf(stdout, "will come after sleeping 5 seconds\n");
   
   sleep(5);
}

/*
6	int fgetpos(FILE *stream, fpos_t *pos)
Gets the current file position of the stream and writes it to pos.
*/
void fgetpos_t()
{
   FILE *fp;
   fpos_t position;

   fp = fopen("file.txt","w+");
   fgetpos(fp, &position);
   fputs("Hello, World!", fp);
  
   fsetpos(fp, &position);
   fputs("This is going to override previous content", fp);
   fclose(fp);
}

/*
7	FILE *fopen(const char *filename, const char *mode)
Opens the filename pointed to by filename using the given mode.
1	 "r"
Opens a file for reading. The file must exist.
2	"w"
Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
3	"a"
Appends to a file. Writing operations, append data at the end of the file. The file is created if it does not exist.
4	"r+"
Opens a file to update both reading and writing. The file must exist.
5	"w+"
Creates an empty file for both reading and writing.
6	"a+"
Opens a file for reading and appending.
*/
void fopen_t()
{
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);

   int c;
  
   fp = fopen("file.txt","r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);
}

/*
8	size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
Reads data from the given stream into the array pointed to by ptr.
ptr − This is the pointer to a block of memory with a minimum size of size*nmemb bytes.
size − This is the size in bytes of each element to be read.
nmemb − This is the number of elements, each one with a size of size bytes.
stream − This is the pointer to a FILE object that specifies an input stream.
The total number of elements successfully read are returned as a size_t object, which is an integral data type. If this number differs from the nmemb parameter, then either an error had occurred or the End Of File was reached.
*/
void fread_t()
{
   FILE *fp;
   char c[] = "this is tutorialspoint";
   char buffer[100];

   /* Open file for both reading and writing */
   fp = fopen("file.txt", "w+");

   /* Write data to the file */
   fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   fseek(fp, 0, SEEK_SET);

   /* Read and display data */
   fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);
}

/*
9	FILE *freopen(const char *filename, const char *mode, FILE *stream)
Associates a new filename with the given open stream and same time closing the old file in stream.
*/
void freopen_t()
{
   FILE *fp;

   printf("This text is redirected to stdout\n");

   fp = freopen("file.txt", "w+", stdout);

   printf("This text is redirected to file.txt\n");

   fclose(fp);

   // re run below part independently will work
   int c;

   fp = fopen("file.txt","r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);
}

/*
10	int fseek(FILE *stream, long int offset, int whence)
Sets the file position of the stream to the given offset. The argument offset signifies the number of bytes to seek from the given whence position.
SEEK_SET
Beginning of file

SEEK_CUR
Current position of the file pointer

SEEK_END
End of file
*/
void fseek_t()
{
   FILE *fp;

   fp = fopen("file.txt","w+");
   fputs("This is tutorialspoint.com", fp);
  
   fseek( fp, 7, SEEK_SET );
   fputs(" C Programming Language", fp);
   fclose(fp);

   int c;

   fp = fopen("file.txt","r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break;
      }
      printf("%c", c); 
   }
   fclose(fp);
}

/*
11	int fsetpos(FILE *stream, const fpos_t *pos)
Sets the file position of the given stream to the given position. The argument pos is a position given by the function fgetpos.
*/
void fsetpos_t()
{
   FILE *fp;
   fpos_t position;

   fp = fopen("file.txt","w+");
   fgetpos(fp, &position);
   fputs("Hello, World!", fp);
  
   fsetpos(fp, &position);
   fputs("This is going to override previous content", fp);
   fclose(fp);
}

/*
12	long int ftell(FILE *stream)
Returns the current file position of the given stream.
*/
void ftell_t()
{
   FILE *fp;
   int len;

   fp = fopen("file.txt", "r");
   if( fp == NULL )  {
      perror ("Error opening file");
      return;
   }
   fseek(fp, 0, SEEK_END);

   len = ftell(fp);
   fclose(fp);

   printf("Total size of file.txt = %d bytes\n", len);
}

/*
13	size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
Writes data from the array pointed to by ptr to the given stream.
    ptr − This is the pointer to the array of elements to be written.
    size − This is the size in bytes of each element to be written.
    nmemb − This is the number of elements, each one with a size of size bytes.
    stream − This is the pointer to a FILE object that specifies an output stream.
*/
void fwrite_t()
{
   FILE *fp;
   char str[] = "This is tutorialspoint.com";

   fp = fopen( "file.txt" , "w" );
   fwrite(str , 1 , sizeof(str) , fp );

   fclose(fp);

   int c;
   fp = fopen("file.txt","r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", c);
   }
   fclose(fp);
}

/*
14	int remove(const char *filename)
Deletes the given filename so that it is no longer accessible.
*/
void remove_t()
{
   int ret;
   FILE *fp;
   char filename[] = "file.txt";

   fp = fopen(filename, "w");

   fprintf(fp, "%s", "This is tutorialspoint.com");
   fclose(fp);
   
   ret = remove(filename);

   if(ret == 0) {
      printf("File deleted successfully");
   } else {
      printf("Error: unable to delete the file");
   }
}

/*
15	int rename(const char *old_filename, const char *new_filename)
Causes the filename referred to, by old_filename to be changed to new_filename.
*/
void rename_t()
{
   int ret;
   char oldname[] = "./file.txt";
   char newname[] = "./newfile.txt";
   
   ret = rename(oldname, newname);
	
   if(ret == 0) {
      printf("File renamed successfully");
   } else {
      printf("Error: unable to rename the file error %d %s", errno, strerror(errno));
   }
}

/*
16	void rewind(FILE *stream)
Sets the file position to the beginning of the file of the given stream.
*/
void rewind_t()
{
   char str[] = "This is tutorialspoint.com";
   FILE *fp;
   int ch;

   /* First let's write some content in the file */
   fp = fopen( "file.txt" , "w" );
   fwrite(str , 1 , sizeof(str) , fp );
   fclose(fp);

   fp = fopen( "file.txt" , "r" );
   while(1) {
      ch = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", ch);
   }
   rewind(fp);
   printf("\n");
   while(1) {
      ch = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", ch);
     
   }
   fclose(fp);
}

/*
17	void setbuf(FILE *stream, char *buffer)
Defines how a stream should be buffered.
The C library function void setbuf(FILE *stream, char *buffer) defines how a stream should be buffered. This function should be called once the file associated with the stream has already been opened, but before any input or output operation has taken place.
    stream − This is the pointer to a FILE object that identifies an open stream.
    buffer − This is the user allocated buffer. This should have a length of at least BUFSIZ bytes, which is a macro constant to be used as the length of this array.
*/
void setbuf_t()
{
   char buf[BUFSIZ];

   setbuf(stdout, buf);
   puts("This is tutorialspoint from setbuf");

   fflush(stdout);
}

/*
18	int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
Another function to define how a stream should be buffered.
    stream − This is the pointer to a FILE object that identifies an open stream.
    buffer − This is the user allocated buffer. If set to NULL, the function automatically allocates a buffer of the specified size.
    mode − This specifies a mode for file buffering −
        _IOFBF
        Full buffering − On output, data is written once the buffer is full. On Input the buffer is filled when an input operation is requested and the buffer is empty.

        _IOLBF
        Line buffering − On output, data is written when a newline character is inserted into the stream or when the buffer is full, what so ever happens first. On Input, the buffer is filled till the next newline character when an input operation is requested and buffer is empty.

        _IONBF
        No buffering − No buffer is used. Each I/O operation is written as soon as possible. The buffer and size parameters are ignored.

    size − This is the buffer size in bytes
*/
void setvbuf_t()
{
   char buff[1024];

   memset( buff, '\0', sizeof( buff ));

   fprintf(stdout, "Going to set full buffering on\n");
   setvbuf(stdout, buff, _IOFBF, 1024);

   fprintf(stdout, "This is tutorialspoint.com\n");
   fprintf(stdout, "This output will go into buff\n");
   fflush( stdout );

   fprintf(stdout, "and this will appear when programm\n");
   fprintf(stdout, "will come after sleeping 5 seconds\n");

   sleep(5);
}

/*
19	FILE *tmpfile(void)
Creates a temporary file in binary update mode (wb+).
*/
void tmpfile_t()
{
   FILE *fp;

   fp = tmpfile();
   printf("Temporary file created\n");

   /* you can use tmp file here */

   fclose(fp);
}

/*
20	char *tmpnam(char *str)
Generates and returns a valid temporary filename which does not exist.
void tmpnam_t()
{
   char buffer[L_tmpnam];
   char *ptr;

   tmpnam(buffer);
   printf("Temporary name 1: %s\n", buffer);
 
   ptr = tmpnam(NULL);
   printf("Temporary name 2: %s\n", ptr);
}
*/

/*
21	int fprintf(FILE *stream, const char *format, ...)
Sends formatted output to a stream.
format − This is the C string that contains the text to be written to the stream. It can optionally contain embedded format tags that are replaced by the values specified in subsequent additional arguments and formatted as requested. Format tags prototype is %[flags][width][.precision][length]specifier, which is explained below −
c
Character

d or i
Signed decimal integer

e
Scientific notation (mantissa/exponent) using e character

E
Scientific notation (mantissa/exponent) using E character

f
Decimal floating point

Uses the shorter of %e or %f
G
Uses the shorter of %E or %f

o
Signed octal

s
String of characters

u
Unsigned decimal integer

x
Unsigned hexadecimal integer

X
Unsigned hexadecimal integer (capital letters)

p
Pointer address

n
Nothing printed

%
Character

Sr.No.	Flags & Description
-
Left-justifies within the given field width; Right justification is the default (see width sub-specifier).

+
Forces to precede the result with a plus or minus sign (+ or -) even for positive numbers. By default, only negative numbers are preceded with a -ve sign.

(space)
If no sign is written, a blank space is inserted before the value.

#
Used with o, x or X specifiers. The value is preceded with 0, 0x or 0X respectively for values different than zero. Used with e, E and f, it forces the written output to contain a decimal point even if no digits would follow. By default, if no digits follow then no decimal point is written. Used with g or G the result is the same as with e or E but trailing zeros are not removed.

0
Left-pads the number with zeroes (0) instead of spaces, where padding is specified (see width sub-specifier).

Width & Description
(number)
Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.

*
The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.

.precision & Description
.number
For integer specifiers (d, i, o, u, x, X) − precision specifies the minimum number of digits to be written. If the value to be written is shorter than this number, the result is padded with leading zeros. The value is not truncated even if the result is longer. A precision of 0 means that no character is written for the value 0. For e, E and f specifiers: this is the number of digits to be printed after the decimal point. For g and G specifiers: This is the maximum number of significant digits to be printed. For s: this is the maximum number of characters to be printed. By default all characters are printed until the ending null character is encountered. For c type: it has no effect. When no precision is specified, the default is 1. If the period is specified without an explicit value for precision, 0 is assumed.
.*
The precision is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.

Length & Description
h
The argument is interpreted as a short int or unsigned short int (only applies to integer specifiers: i, d, o, u, x and X).

l
The argument is interpreted as a long int or unsigned long int for integer specifiers (i, d, o, u, x and X), and as a wide character or wide character string for specifiers c and s.

L
The argument is interpreted as a long double (only applies to floating point specifiers: e, E, f, g and G).
*/
void fprintf_t()
{
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fprintf(fp, "%s %s %s %d", "We", "are", "in", 2012);
   
   fclose(fp);
}

/*
22	int printf(const char *format, ...)
Sends formatted output to stdout.
*/
void printf_t()
{
   int ch;

   for( ch = 75 ; ch <= 100; ch++ ) {
      printf("ASCII value = %d, Character = %c\n", ch , ch );
   }
}

/*
23	int sprintf(char *str, const char *format, ...)
Sends formatted output to a string.
*/
void sprintf_t()
{
   char str[80];

   sprintf(str, "Value of Pi = %f", M_PI);
   puts(str);
}

/*
24	int vfprintf(FILE *stream, const char *format, va_list arg)
Sends formatted output to a stream using an argument list.
*/
void WriteFrmtd(FILE *stream, char *format, ...) {
   va_list args;

   va_start(args, format);
   vfprintf(stream, format, args);
   va_end(args);
}

void vfprintf_t()
{
   FILE *fp;

   fp = fopen("file.txt","w");

   WriteFrmtd(fp, "This is just one argument %d \n", 10);

   fclose(fp);
}

/*
25	int vprintf(const char *format, va_list arg)
Sends formatted output to stdout using an argument list.
*/
void vWriteFrmtd(char *format, ...) {
   va_list args;
   
   va_start(args, format);
   vprintf(format, args);
   va_end(args);
}
void vprintf_t()
{
   vWriteFrmtd("%d variable argument\n", 1);
   vWriteFrmtd("%d variable %s\n", 2, "arguments");
}

/*
26	int vsprintf(char *str, const char *format, va_list arg)
Sends formatted output to a string using an argument list.
*/
char buffer[80];
int vspfunc(char *format, ...) {
   va_list aptr;
   int ret;

   va_start(aptr, format);
   ret = vsprintf(buffer, format, aptr);
   va_end(aptr);

   return(ret);
}

void vsprintf_t() {
   int i = 5;
   float f = 27.0;
   char str[50] = "tutoriaspoint.com";

   vspfunc("%d %f %s", i, f, str);
   printf("%s\n", buffer);
}

/*
27	int fscanf(FILE *stream, const char *format, ...)
Reads formatted input from a stream.
*/
void fscanf_t()
{
   char str1[10], str2[10], str3[10];
   int year;
   FILE * fp;

   fp = fopen ("file.txt", "w+");
   fputs("We are in 2012", fp);
   
   rewind(fp);
   fscanf(fp, "%s %s %s %d", str1, str2, str3, &year);
   
   printf("Read String1 |%s|\n", str1 );
   printf("Read String2 |%s|\n", str2 );
   printf("Read String3 |%s|\n", str3 );
   printf("Read Integer |%d|\n", year );

   fclose(fp);
}

/*
28	int scanf(const char *format, ...)
Reads formatted input from stdin.
*/
void scanf_t()
{
   char str1[20], str2[30];

   printf("Enter name: ");
   scanf("%s", str1);

   printf("Enter your website name: ");
   scanf("%s", str2);

   printf("Entered Name: %s\n", str1);
   printf("Entered Website:%s", str2);
}

/*
29	int sscanf(const char *str, const char *format, ...)
Reads formatted input from a string.
*/
void sscanf_t()
{
   int day, year;
   char weekday[20], month[20], dtm[100];

   strcpy( dtm, "Saturday March 25 1989" );
   sscanf( dtm, "%s %s %d  %d", weekday, month, &day, &year );

   printf("%s %d, %d = %s\n", month, day, year, weekday );
}

/*
30	int fgetc(FILE *stream)
Gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream.
*/
void fgetc_t()
{
   FILE *fp;
   int c;
   int n = 0;
  
   fp = fopen("file.txt","r");
   if(fp == NULL) {
      perror("Error in opening file");
      return;
   } do {
      c = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      printf("%c", c);
   } while(1);

   fclose(fp);
}

/*
31	char *fgets(char *str, int n, FILE *stream)
Reads a line from the specified stream and stores it into the string pointed to by str. It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached, whichever comes first.
*/
void fgets_t()
{
   FILE *fp;
   char str[60];

   /* opening file for reading */
   fp = fopen("file.txt" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return;
   }
   if( fgets (str, 60, fp)!=NULL ) {
      /* writing content to stdout */
      puts(str);
   }
   fclose(fp);
}

/*
32	int fputc(int char, FILE *stream)
Writes a character (an unsigned char) specified by the argument char to the specified stream and advances the position indicator for the stream.
*/
void fputc_t()
{
   FILE *fp;
   int ch;

   fp = fopen("file.txt", "w+");
   for( ch = 33 ; ch <= 100; ch++ ) {
      fputc(ch, fp);
   }
   fclose(fp);
}

/*
33	int fputs(const char *str, FILE *stream)
Writes a string to the specified stream up to but not including the null character.
*/
void fputs_t()
{
   FILE *fp;

   fp = fopen("file.txt", "w+");

   fputs("This is c programming.", fp);
   fputs("This is a system programming language.", fp);

   fclose(fp);
}

/*
34	int getc(FILE *stream)
Gets the next character (an unsigned char) from the specified stream and advances the position indicator for the stream.
*/
void getc_t()
{
   char c;

   printf("Enter character: ");
   c = getc(stdin);
   printf("Character entered: ");
   putc(c, stdout);
}

/*
35	int getchar(void)
Gets a character (an unsigned char) from stdin.
*/
void getchar_t()
{
   char c;
 
   printf("Enter character: ");
   c = getchar();
 
   printf("Character entered: ");
   putchar(c);
}

/*
36	char *gets(char *str)
Reads a line from stdin and stores it into the string pointed to by, str. It stops when either the newline character is read or when the end-of-file is reached, whichever comes first.
*/
void gets_t()
{
   char str[50];

   printf("Enter a string : ");
   gets(str);

   printf("You entered: %s", str);
}

/*
37	int putc(int char, FILE *stream)
Writes a character (an unsigned char) specified by the argument char to the specified stream and advances the position indicator for the stream.
*/
void putc_t()
{
   FILE *fp;
   int ch;

   fp = fopen("file.txt", "w");
   for( ch = 33 ; ch <= 100; ch++ ) {
      putc(ch, fp);
   }
   fclose(fp);
}

/*
38	int putchar(int char)
Writes a character (an unsigned char) specified by the argument char to stdout.
*/
void putchar_t()
{
   char ch;

   for(ch = 'A' ; ch <= 'Z' ; ch++) {
      putchar(ch);
   }
}

/*
39	int puts(const char *str)
Writes a string to stdout up to but not including the null character. A newline character is appended to the output.
*/
void puts_t()
{
   char str1[15];
   char str2[15];

   strcpy(str1, "tutorialspoint");
   strcpy(str2, "compileonline");

   puts(str1);
   puts(str2);
}

/*
40	int ungetc(int char, FILE *stream)
Pushes the character char (an unsigned char) onto the specified stream so that the next character is read.
*/
void ugetc_t()
{
   FILE *fp;
   int c;
   char buffer [256];

   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror("Error in opening file");
      return;
   }
   while(!feof(fp)) {
      c = getc (fp);
      /* replace ! with + */
      if( c == '!' ) {
         ungetc ('+', fp);
      } else {
         ungetc(c, fp);
      }
      fgets(buffer, 255, fp);
      fputs(buffer, stdout);
   }
}

/*
41	void perror(const char *str)
Prints a descriptive error message to stderr. First the string str is printed followed by a colon and then a space.
*/
void perror_t()
{
   FILE *fp;

   /* first rename if there is any file */
   rename("file.txt", "newfile.txt");

   /* now let's try to open same file */
   fp = fopen("file.txt", "r");
   if( fp == NULL ) {
      perror("Error: ");
      return;
   }
   fclose(fp);
}


int main()
{

    clearerr_t();
    ferror_t();
    fclose_t();
    feof_t();
    //fflush_t();
    fgetpos_t();
    fopen_t();
    fread_t();
    //freopen_t();
    fseek_t();
    fsetpos_t();
    ftell_t();
    fwrite_t();
    remove_t();
    rename_t();
    rewind_t();
    //setbuf_t();
    //setvbuf_t();
    tmpfile_t();
    // deprecated, using mkstemp instead
    //tmpnam_t();
    fprintf_t();
    printf_t();
    sprintf_t();
    vfprintf_t();
    vprintf_t();
    vsprintf_t();
    fscanf_t();
    //scanf_t();
    sscanf_t();
    fgetc_t();
    fgets_t();
    fputc_t();
    fputs_t();
    //getc_t();
    //getchar_t();
    //gets_t();
    putc_t();
    putchar_t();
    puts_t();
    //ugetc_t();
    perror_t();

    return 0;
}
