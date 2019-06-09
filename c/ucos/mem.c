#include "define.h"

#define OS_MAX_MEM_PART 10

extern OS_MEM *OSMemFreeList;

OS_MEM *OSMemInit(UINT8 *err)
{
    OS_MEM *plist = (OS_MEM *)malloc(sizeof(OS_MEM));
    if(plist == (OS_MEM *)0) {
        *err = OS_NO_MEM;
        return (OS_MEM *)0;
    }

    OS_MEM *pnext = plist; 
    for(UINT8 i = 0; i < OS_MAX_MEM_PART - 1; i++) {
        pnext->OSMemFreeList = (OS_MEM *)malloc(sizeof(OS_MEM));
        if(pnext->OSMemFreeList == (OS_MEM *)0) {
            *err = OS_NO_MEM;
            return (OS_MEM *)0;
        }
        pnext = pnext->OSMemFreeList;
    } 
    pnext->OSMemFreeList = (OS_MEM *)0;
    *err = OS_NO_ERR;
    return plist;
}

OS_MEM *OSMemCreate(void *addr, UINT32 nblks, UINT32 blksize, UINT8 *err)
{
    OS_MEM *pmem;
    UINT8 *pblk;
    void **plink;
    UINT32 i;

    if(addr == (void *)0) {
        *err = OS_MEM_INVALID_ADDR;
        return((OS_MEM *)0);
    }

    if(nblks < 2) {
        *err = OS_MEM_INVALID_BLKS;
        return((OS_MEM *)0);
    }

    if(blksize < sizeof(void *)) {
        *err = OS_MEM_INVALID_SIZE;
        return((OS_MEM *)0);
    }

    pmem = OSMemFreeList;
    if(OSMemFreeList != (OS_MEM *)0) {
        OSMemFreeList = (OS_MEM *)OSMemFreeList->OSMemFreeList;
    }

    if(pmem == (OS_MEM *)0) {
        *err = OS_MEM_INVALID_PART;
        return((OS_MEM *)0);
    }

    plink = (void **)addr;
    pblk = (UINT8 *)addr + blksize;
    for(int i = 0; i < nblks - 1; i++) {
        *plink = pblk;
        plink = (void **)pblk;
        pblk += blksize; 
    }
    *plink = (void*)0;

    pmem->OSMemAddr = addr;
    pmem->OSMemFreeList = addr;
    pmem->OSMemNFree = nblks;
    pmem->OSMemNBlks = nblks;
    pmem->OSMemBlkSize = blksize;
    *err = OS_NO_ERR;

    return(pmem);
}

void *OSMemGet(OS_MEM *pmem, UINT8 *err)
{
    void *pblk;

    if(pmem == (OS_MEM *)0) {
        *err = OS_MEM_INVALID_PMEM;
        return((OS_MEM *)0);
    }

    if(pmem->OSMemNFree > 0) {
        pblk = pmem->OSMemFreeList;
        pmem->OSMemFreeList = *(void **)pblk;
        pmem->OSMemNFree--;
        *err = OS_NO_ERR;
        return (pblk);
    }
    *err = OS_MEM_NO_FREE_BLKS;
    return ((void *)0);
}

UINT8 OSMemPut(OS_MEM *pmem, void *pblk)
{
    if(pmem == (OS_MEM *)0) {
        return (OS_MEM_INVALID_PMEM);
    }

    if(pblk == (void *)0) {
        return (OS_MEM_INVALID_PBLK);
    }

    if(pmem->OSMemNFree >= pmem->OSMemNBlks) {
        return (OS_MEM_FULL);
    }

    *(void**)pblk = pmem->OSMemFreeList;
    pmem->OSMemFreeList = pblk;
    pmem->OSMemNFree++;

    return (OS_NO_ERR);
}

UINT8 OSMemQuery(OS_MEM *pmem, OS_MEM_DATA *pdata)
{
    if(pmem == (OS_MEM *)0) {
        return (OS_MEM_INVALID_PMEM);
    }

    if(pdata == (OS_MEM_DATA *)0) {
        return (OS_MEM_INVALID_PDATA);
    }

    pdata->OSAddr = pmem->OSMemAddr;
    pdata->OSFreeList = pmem->OSMemFreeList;
    pdata->OSBlkSize = pmem->OSMemBlkSize;
    pdata->OSNBlks = pmem->OSMemNBlks;
    pdata->OSNFree = pmem->OSMemNFree;
    pdata->OSNUsed = pdata->OSNBlks - pdata->OSNFree;

    return (OS_NO_ERR);
}

void OSMemPrint(OS_MEM *pmem)
{
    printf("Mem layout:\n");
    UINT8 *pblk = (UINT8 *)pmem->OSMemAddr;

    for(UINT8 i = 0; i < pmem->OSMemNBlks; i++) {
        printf("addr: 0x%p  | val = 0x%lx\n", (void *)pblk, *(UINT64 *)pblk);
        pblk += pmem->OSMemBlkSize;
    }
}

void OSMemDataPrint(OS_MEM_DATA *pdata)
{
    printf("Mem Data layout:\n");
    printf("pdata->OSAddr = 0x%p\n", pdata->OSAddr);
    printf("pdata->OSFreeList = 0x%p\n", pdata->OSFreeList);
    printf("pdata->OSBlkSize = %d\n", pdata->OSBlkSize);
    printf("pdata->OSNBlks = %d\n", pdata->OSNBlks);
    printf("pdata->OSNFree = %d\n", pdata->OSNFree);
    printf("pdata->OSNUsed = %d\n", pdata->OSNUsed);
}
