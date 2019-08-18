/*
实现支持下列接口的「快照数组」- SnapshotArray：

SnapshotArray(int length) - 初始化一个与指定长度相等的 类数组 的数据结构。初始时，每个元素都等于 0。
void set(index, val) - 会将指定索引 index 处的元素设置为 val。
int snap() - 获取该数组的快照，并返回快照的编号 snap_id（快照号是调用 snap() 的总次数减去 1）。
int get(index, snap_id) - 根据指定的 snap_id 选择快照，并返回该快照指定索引 index 的值。
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} listnode;

typedef struct {
    int id; 
    int len;
    listnode **head;
} SnapshotArray;


SnapshotArray* snapshotArrayCreate(int length) {
    SnapshotArray *snap = (SnapshotArray *)malloc(sizeof(SnapshotArray));     
    snap->id = 0;
    snap->len = length;
    listnode **h = (listnode **)malloc(sizeof(listnode *) * length);     
    snap->head = h; 
    for(int i = 0; i < length; i++) {
        listnode *node = (listnode *)malloc(sizeof(listnode));     
        node->data = 0;
        node->next = NULL;
        snap->head[i] = node;
    }
    return snap;
}

void snapshotArraySet(SnapshotArray* obj, int index, int val) {
    listnode *p = obj->head[index];
    while(p->next)
        p = p->next;
    p->data = val;
}

int snapshotArraySnap(SnapshotArray* obj) {
    for(int i = 0; i < obj->len; i++) {
        listnode *node = (listnode *)malloc(sizeof(listnode));     
        node->data = 0;
        node->next = NULL;

        listnode *p = obj->head[i];
        while(p->next)
            p = p->next;
        p->next = node;
        node->data = p->data;
    }
    return obj->id++;
}

int snapshotArrayGet(SnapshotArray* obj, int index, int snap_id) {
    listnode *p = obj->head[index];
    while(snap_id) {
        p = p->next;
        snap_id--;
    }
    return p->data;
}

void snapshotArrayFree(SnapshotArray* obj) {
    for(int i = 0; i < obj->len; i++) {
        listnode *p = obj->head[i];
        listnode *r = p->next;
        while(r) {
            free(p);
            p = r;
            r = r->next;
        }
        free(p);
    }
    for(int i = 0; i < obj->len; i++) {
        free(obj->head[i]);
    }
    free(obj->head);
}

/**
 * Your SnapshotArray struct will be instantiated and called as such:
 * SnapshotArray* obj = snapshotArrayCreate(length);
 * snapshotArraySet(obj, index, val);
 
 * int param_2 = snapshotArraySnap(obj);
 
 * int param_3 = snapshotArrayGet(obj, index, snap_id);
 
 * snapshotArrayFree(obj);
*/

int main()
{
    return 0;
}
