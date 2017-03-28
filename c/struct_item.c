#include <stdio.h>
#include <stdlib.h>

typedef struct _DL_LIST {
    struct _DL_LIST *pPrev;
    struct _DL_LIST *pNext;
	int v;
} ATH_DL_LIST, *PDL_LIST;

typedef struct _QCA_PACKET_QUEUE {
	ATH_DL_LIST      QueueHead;
	int              Depth;
} QCA_PACKET_QUEUE;

typedef struct combuf_bsp
{
	struct combuf_bsp *next;
	int *head;
	int *end;
	int len;
} combuf_bsp;

typedef struct bl_net_impl_obj
{
	char name[10];
	int unit;
	int dev;
} BL_NET_IMPL_OBJ;

typedef struct _QCA_PACKET {
	ATH_DL_LIST        ListLink;       /* double link */
	/*Node content */
	int v2;
	combuf_bsp*        skb;
	BL_NET_IMPL_OBJ    *end;
} QCA_PACKET;

typedef struct _QCA_TX_ENGINE {
	int                pktProcessing;
	/*Sem*/
	int              qSem;
	QCA_PACKET_QUEUE    txQueue;
}QCA_TX_ENGINE;

#define DL_LIST_INIT(pList) {(pList)->pPrev = pList; (pList)->pNext = pList;}

#define A_CONTAINING_STRUCT(address, struct_type, field_name)\
            ((struct_type *)((char *)(address) - (char *)(&((struct_type *)0)->field_name)))
int main()
{
	int i;
	ATH_DL_LIST *pItem = calloc(sizeof(ATH_DL_LIST), 1);	
	DL_LIST_INIT(pItem)
	char *c1 = (char *)(&((QCA_PACKET *)0)->ListLink);	
	char *c2 = (char *)(&((QCA_PACKET *)0)->v2);	
	char *c3 = (char *)(&((QCA_PACKET *)0)->skb);	
	char *c4 = (char *)(&((QCA_PACKET *)0)->end);	
	printf("char * c1= %p\n", c1);	
	printf("char * c2= %p\n", c2);	
	printf("char * c3= %p\n", c3);	
	printf("char * c4= %p\n", c4);	

	return 0;
}
