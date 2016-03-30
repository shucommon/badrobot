#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
 * container_of - cast a member of a structure out to the containing structure
 * _ptr:    the pointer to the member.
 * _type:   the type of the container struct this is embedded in.
 * _member: the name of the member within the struct.
 *
 */
#define container_of( _ptr, _type, _member) ({ \
            const typeof( ((_type *)0)->_member ) *__mptr = (_ptr);    \
            (_type *)( (u_int8_t *)__mptr - offsetof(_type,_member) ); \
    })

struct num
{
	int a;
	int b;
	int c;
};


int main()
{
	struct num n;
	int *ptr = &n.b;
	struct num* n_ptr;
	n_ptr = container_of(ptr, struct num, b);

	printf("address n = %p\n", (void*)(&n));
	printf("address n.a = %p\n", (void*)(&n.a));
	printf("address n.b = %p\n", (void*)(&n.b));
	printf("address n.c = %p\n", (void*)(&n.c));
	printf("address ptr = %p\n", (void*)(ptr));
	printf("address n_ptr = %p\n", (void*)(n_ptr));
	
	return 0;
}
