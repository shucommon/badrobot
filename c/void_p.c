#include <stdio.h>

typedef struct stored_callback_t {
    void *addr[2];
    char *name;
} stored_callback_t;

stored_callback_t table[10] =
{
    { { NULL, NULL }, "DeaIPTableFreeFunc" },
    { { NULL, NULL }, "SSLSpyChkUserAuthOnZone" },
    { { NULL, NULL }, "acChkUserAuthOnZone" },
    { { NULL, NULL }, "addrObjAtomCompare" },
    { { NULL, NULL }, "addrObjAtomGetKey" },
    { { NULL, NULL }, "afChkUserAuthOnZone" },
    { { NULL, NULL }, "afClassifyPacket" },
    { { NULL, NULL }, "afPolicy_Cb" },
    { { NULL, NULL }, "afPolicy_Cb_file scan" },
	{ { NULL, NULL }, "qca98pacifists" }
};

typedef int (*BSP_END_SEND_BUF)(int v1, int v2);
typedef struct
{
	char *name;
	BSP_END_SEND_BUF send_buffer;
} END_BSP;

void stored_callback_set(void *addr, void *val)
{
	stored_callback_t *row;
	void **loc = addr;
	int i;

	if (val == NULL) {
		*loc = NULL;
		return;
	}

	for (i = 0; i < 10; i++) {
		row = &table[i];
		printf("row->name:%s\n", row->name);
		if(row->addr[0] == val) {
			*loc = row;
			printf("success ed\n");
			return;
		}
	}	
}

int qca98acIfaceTx(int v1, int v2)
{
	return 0;
}

END_BSP end_bsp =
{
	"qca98ac",
	(BSP_END_SEND_BUF)NULL
};

	
int main(int argc, char* argv[])
{
	stored_callback_set(end_bsp.send_buffer, qca98acIfaceTx);

	return 0;
}
