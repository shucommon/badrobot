#include <stdio.h>
#include <stdlib.h>
/*
 * dbg hash definitions.
 * Hashing makes finding module information faster.
 */
#define DBG_HASH_SHIFT 8
#define DBG_N_HASH (1<<DBG_HASH_SHIFT)
#define DBG_HASH_MASK (DBG_N_HASH-1)

/*
 * dbgHashMake -- compute hash of name
 */
unsigned dbgHashMake(const char *Name)
{
	unsigned hash = 0;
	int i = 0;
	while(*Name) {
		hash = (hash << 1) | (1 & (hash >> (DBG_HASH_SHIFT - 1)));
		printf("%d hash int %d, hex 0x%x\n", i++, hash, hash);
		hash ^= *Name++;
		printf("%d hash int %d, hex 0x%x\n", i++, hash, hash);
	}
	hash &= DBG_HASH_MASK;
	printf("final value hash %d 0x%x\n", hash, hash);
	return hash;
}

int main(void)
{
	char *guo = (char*)malloc(100);
	while(printf("input: ") && scanf("%s", guo) != EOF)	
	{
		dbgHashMake(guo);
	}

	return 0;
}
