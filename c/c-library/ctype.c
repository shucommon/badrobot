/*
The ctype.h header file of the C Standard Library declares several functions that are useful for testing and mapping characters.
All the functions accepts int as a parameter, whose value must be EOF or representable as an unsigned char.
All the functions return non-zero (true) if the argument c satisfies the condition described, and zero(false) if not
*/

/*
1	int isalnum(int c)
This function checks whether the passed character is alphanumeric.

2	int isalpha(int c)
This function checks whether the passed character is alphabetic.

3	int iscntrl(int c)
This function checks whether the passed character is control character.

4	int isdigit(int c)
This function checks whether the passed character is decimal digit.

5	int isgraph(int c)
This function checks whether the passed character has graphical representation using locale.

6	int islower(int c)
This function checks whether the passed character is lowercase letter.

7	int isprint(int c)
This function checks whether the passed character is printable.

8	int ispunct(int c)
This function checks whether the passed character is a punctuation character.

9	int isspace(int c)
This function checks whether the passed character is white-space.

10	int isupper(int c)
This function checks whether the passed character is an uppercase letter.

11	int isxdigit(int c)
This function checks whether the passed character is a hexadecimal digit.
*/

/*
Character Classes
Sr.No.	Character Class & Description
1	
Digits
This is a set of whole numbers { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.
isdigit

2	
Hexadecimal digits
This is the set of { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }.
isxdigit

3	
Lowercase letters
This is a set of lowercase letters { a b c d e f g h i j k l m n o p q r s t u v w x y z }.
islower

4	
Uppercase letters
This is a set of uppercase letters {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }.
isupper

5	
Letters
This is a set of lowercase and uppercase letters.

6	
Alphanumeric characters
This is a set of Digits, Lowercase letters and Uppercase letters.
isalnum()

7	
Punctuation characters
This is a set of ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~
ispunct

8	
Graphical characters
This is a set of Alphanumeric characters and Punctuation characters.
isgraph

9	
Space characters
This is a set of tab, newline, vertical tab, form feed, carriage return, and space.
isspace
' '   (0x20)	space (SPC)
'\t'	(0x09)	horizontal tab (TAB)
'\n'	(0x0a)	newline (LF)
'\v'	(0x0b)	vertical tab (VT)
'\f'	(0x0c)	feed (FF)
'\r'	(0x0d)	carriage return (CR)

10	
Printable characters
This is a set of Alphanumeric characters, Punctuation characters and Space characters.
isprint

11	
Control characters
In ASCII, these characters have octal codes 0 through 0x1f, and 0x7f(DEL).
iscntrl

12	
Blank characters
These are spaces and tabs.

13	
Alphabetic characters
This is a set of Lowercase letters and Uppercase letters.
isalpha
*/

/*
Sr.No.	Function & Description
1	int tolower(int c)
This function converts uppercase letters to lowercase.
This function returns lowercase equivalent to c, if such value exists, else c remains unchanged. The value is returned as an int value that can be implicitly casted to char.

2	int toupper(int c)
This function converts lowercase letters to uppercase.
This function returns uppercase equivalent to c, if such value exists, else c remains unchanged. The value is returned as an int value that can be implicitly casted to char.
*/


#include <stdio.h>
#include <ctype.h>

int main()
{
    int var1 = 'd';
    int var2 = '2';
    int var3 = '\t';
    int var4 = ' '; 

    int var = var1;

    if( isalnum(var) )
        printf("1 var = |%c|\n", var);
    if( isalpha(var) )
        printf("2 var = |%c|\n", var);
    if( iscntrl(var) )
        printf("3 var = |%c|\n", var);
    if( isdigit(var) )
        printf("4 var = |%c|\n", var);
    if( isgraph(var) )
        printf("5 var = |%c|\n", var);
    if( islower(var) )
        printf("6 var = |%c|\n", var);
    if( isprint(var) )
        printf("7 var = |%c|\n", var);
    if( ispunct(var) )
        printf("8 var = |%c|\n", var);
    if( isspace(var) )
        printf("9 var = |%c|\n", var);
    if( isupper(var) )
        printf("10 var = |%c|\n", var);
    if( isxdigit(var) )
        printf("11 var = |%c|\n", var);
    
    printf("var = |%c|\n", tolower(var));
    printf("var = |%c|\n", toupper(var));

    return 0;
}
