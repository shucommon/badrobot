#include "define.h"

OS_MEM *OSMemFreeList;
OS_MEM *pmem;
UINT8 buf[100][32];

int main()
{
    UINT8 err;
    OSMemFreeList = OSMemInit(&err);
    if(err != OS_NO_ERR)
        return -1;

    pmem = OSMemCreate(buf, 100, 32, &err);
    if(err != OS_NO_ERR)
        return -1;
    OSMemPrint(pmem);

    OS_MEM_DATA *pdata;
    OSMemQuery(pmem, pdata);
    OSMemDataPrint(pdata);

    UINT8 *pblk;
    pblk = OSMemGet(pmem, &err);
    if(err != OS_NO_ERR)
        return -1;

    OSMemQuery(pmem, pdata);
    OSMemDataPrint(pdata);

    err = OSMemPut(pmem, pblk);
    if(err != OS_NO_ERR)
        return -1;

    OSMemQuery(pmem, pdata);
    OSMemDataPrint(pdata);
}
