#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int UINT64;
typedef unsigned int UINT32;
typedef unsigned char UINT8;

typedef struct {
    void *OSMemAddr;
    void *OSMemFreeList;
    UINT32 OSMemBlkSize; 
    UINT32 OSMemNBlks; 
    UINT32 OSMemNFree; 
} OS_MEM;

typedef struct {
    void *OSAddr;
    void *OSFreeList;
    UINT32 OSBlkSize;
    UINT32 OSNBlks;
    UINT32 OSNFree;
    UINT32 OSNUsed;
} OS_MEM_DATA;

enum {
    OS_NO_ERR,
    OS_MEM_INVALID_ADDR,
    OS_MEM_INVALID_BLKS,
    OS_MEM_INVALID_SIZE,
    OS_MEM_INVALID_PART,
    OS_MEM_INVALID_PMEM,
    OS_MEM_NO_FREE_BLKS,
    OS_MEM_INVALID_PBLK,
    OS_MEM_FULL,
    OS_MEM_INVALID_PDATA,
    OS_NO_MEM
};

OS_MEM *OSMemInit(UINT8 *err);
OS_MEM *OSMemCreate(void *addr, UINT32 nblks, UINT32 blksize, UINT8 *err);
void *OSMemGet(OS_MEM *pmem, UINT8 *err);
UINT8 OSMemPut(OS_MEM *pmem, void *pblk);
UINT8 OSMemQuery(OS_MEM *pmem, OS_MEM_DATA *pdata);
void OSMemDataPrint(OS_MEM_DATA *pdata);
void OSMemPrint(OS_MEM *pmem);
