#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;
 
typedef struct {
    ElemType *elem;
    int length;
    int listsize;
} SqList;

Status InitList(SqList *L){
    L->elem =(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if (!L->elem)return ERROR;
    L->length=0;
    L->listsize=LIST_INIT_SIZE;
    return OK;
}

void DestroyList(SqList *L){
    free(L->elem);
    L->elem=NULL;
    L->length= L->listsize=0;
}

/* 在第 i 个位置（1<=i<=length+1）前插入 e */
Status ListInsert(SqList*L,int i,ElemType e){
    if (i<1 || i>L->length+1) return ERROR;
    if (L->length>=L->listsize){
        ElemType *nb = (ElemType *)realloc(L->elem,(L->listsize + LISTINCREMENT)*sizeof(ElemType));
        if (!nb) return ERROR;
        L->elem=nb;
        L->listsize += LISTINCREMENT;
    }
    for (int j = L->length;j >= i; j--)
        L->elem[j] = L->elem[j-1];
    L->elem[i-1] = e;
    L->length++;
    return OK;
}

/* 删除第 i 个元素，用 e 返回 */
Status ListDelete(SqList *L,int i,ElemType *e){
    if (i<1 || i> L->length) return ERROR;
    *e = L->elem[i-1];
    for (int j = i; j< L->length; j++)
        L->elem[j-1] = L->elem[j];
    L->length--;
    return OK;
}

/* 算法2.7：合并两个非递减有序顺序表 La、Lb 为 Lc */
Status MergeSqList(SqList La,SqList Lb,SqList *Lc){
    Lc->listsize = Lc->length = La.length + Lb.length;
    Lc->elem = (ElemType *)malloc(Lc->listsize * sizeof(ElemType));
    if (!Lc->elem) return ERROR;
    int i=0, j=0, k=0;
    while (i<La.length && j<Lb.length){
        if (La.elem[i] <= Lb.elem[j])
           Lc->elem[k++] = La.elem[i++];
        else
            Lc->elem[k++] = Lb.elem[j++];
    }
    while (i < La.length) Lc->elem[k++] = La.elem[i++];
    while (j < Lb.length) Lc->elem[k++] = Lb.elem[j++];
    return OK; 
}

/* 读入 n 个升序整数建表 */
void CreateList(SqList *L,int n){
    InitList(L);
    for (int i=1; i<=n;i++){
        ElemType x;
        scanf("%d",&x);
        ListInsert(L,i,x);
    }
}

void ListTraverse(SqList L){
    for (int i = 0; i < L.length; i++)
        printf("%d ", L.elem[i]);
    printf("\n");
}

int main(void) {
    SqList La, Lb, Lc;
    int  n;
    printf("Enter La:");
    scanf("%d",&n);
    CreateList(&La,n);

    printf("Enter Lb:");
    scanf("%d",&n);
    CreateList(&Lb,n);

    printf("La = "); ListTraverse(La);
    printf("Lb = "); ListTraverse(Lb);

    MergeSqList(La,Lb,&Lc);
    printf("Lc = "); ListTraverse(Lc);
}