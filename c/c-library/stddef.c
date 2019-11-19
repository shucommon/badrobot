/*
The stddef.h header defines various variable types and macros. Many of these definitions also appear in other headers.
1	
ptrdiff_t
This is the signed integral type and is the result of subtracting two pointers.

2	
size_t
This is the unsigned integral type and is the result of the sizeof keyword.

3	
wchar_t
This is an integral type of the size of a wide character constant.
*/

/*
The C library macro offsetof(type, member-designator) results in a constant integer of type size_t which is the offset in bytes of a structure member from the beginning of the structure. The member is given by member-designator, and the name of the structure is given in type.
*/


#include <stddef.h>
#include <stdio.h>

struct address {
    char name[50];
    char street[50];
    int a;
    float b;
    char c;
    int phone;
//} __attribute__((packed));
};

int main () {
    FILE *fp;

    fp = fopen("file.txt", "r");
    if( fp != NULL ) {
        printf("Opend file file.txt successfully\n");
        fclose(fp);
    }

    fp = fopen("nofile.txt", "r");
    if( fp == NULL ) {
        printf("Could not open file nofile.txt\n");
    }

    printf("name offset = %lu byte in address structure.\n",
    offsetof(struct address, name));

    printf("street offset = %lu byte in address structure.\n",
    offsetof(struct address, street));

    printf("a offset = %lu byte in address structure.\n",
    offsetof(struct address, a));

    printf("b offset = %lu byte in address structure.\n",
    offsetof(struct address, b));

    printf("c offset = %lu byte in address structure.\n",
    offsetof(struct address, c));

    printf("phone offset = %lu byte in address structure.\n",
    offsetof(struct address, phone));

    return(0);
}
