#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

Status InitList(LinkList *L) {
    *L = (LinkList)malloc(sizeof(LNode));
    if (!*L) return ERROR;
    (*L)->next = NULL;
    return OK;
}

void DestroyList(LinkList *L){
    LinkList p =*L,q;
    while(p){q = p->next; free(p); p =q ;}
    *L = NULL;
}

int ListLength(LinkList L){
    int n=0;
    for (LinkList p=L->next;p;p=p->next)n++;
    return n;
}

/* 在第 i 个位置前插入 e */
Status ListInsert(LinkList L,int i,ElemType e){
    LinkList p = L; int j=0;
    while(p &&j<i-1){p = p->next;j++;}
    if (!p|| j>i-1) return ERROR;
    LinkList s= (LinkList)malloc(sizeof(LNode));
    if (!s) return ERROR;
    s->data=e;s->next = p->next; p->next = s;
    return OK;
}

/* 删除第 i 个结点，用 e 返回其值 */
Status ListDelete(LinkList L,int i,ElemType *e){
    LinkList p=L;int j=0;
    while(p->next && j<i-1){p=p->next;j++;}
    if (!p->next || j>i-1) return ERROR;
    LinkList q = p->next; *e =q->data;
    p->next =q->next;
    free(q);
    return OK;
}

/* 头插法：读入 n 个数，每个都插在表头 => 表中顺序与输入顺序相反。
   所以要得到升序的 La，输入时应按降序输入 */
   void CreateList_H(LinkList *L,int n){
    InitList(L);
    for (int i =0 ;i<n;i++){
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d",&s->data);
        s->next = (*L)->next;
        (*L)->next =s;
    }
   }

   /* 尾插法：读入 n 个数，每个都接在表尾 => 表中顺序与输入顺序相同。
   所以要得到升序的 Lb，输入时按升序输入 */
void CreateList_T(LinkList *L,int n){
    InitList(L);
    LinkList r = *L;
    for  (int i=0;i<n;i++){
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d",&s->data);
        s->next =NULL;
        r->next =s;
        r=s;
    }
}

void ListTraverse(LinkList L){
    for (LinkList p=L->next;p;p=p->next) printf("%d ",p->data);
    printf("\n");
}

/* (1) 算法2.12：合并两个非递减有序链表，利用原结点，不另开空间。
   合并后 La、Lb 不再使用（Lb 的头结点被释放） */
   void MergeList_L(LinkList *La, LinkList *Lb, LinkList *Lc) {
    LinkList pa = (*La)->next, pb = (*Lb)->next;
    LinkList pc = *Lc = *La;         /* 用 La 的头结点作为 Lc 的头结点 */
    while (pa && pb) {
        if (pa->data <= pb->data) { pc->next = pa; pc = pa; pa = pa->next; }
        else                      { pc->next = pb; pc = pb; pb = pb->next; }
    }
    pc->next = pa ? pa : pb;         /* 插入剩余段 */
    free(*Lb);                       /* 释放 Lb 的头结点 */
    *La = *Lb = NULL;
}
 
/* (2) 删除有序表中的重复元素，相同值只保留一个。O(n) */
void DeleteDuplicates(LinkList L) {
    LinkList p = L->next, q;
    while (p && p->next) {
        if (p->data == p->next->data) {   /* 后继与自己相同，删后继 */
            q = p->next;
            p->next = q->next;
            free(q);
        } else {
            p = p->next;
        }
    }
}
 
/* (3) 就地逆置：把原结点依次摘下，用头插法插回头结点后。O(n)，辅助空间O(1) */
void ReverseList(LinkList L) {
    LinkList p = L->next, q;
    L->next = NULL;
    while (p) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}
 
int main(void) {
    LinkList La, Lb, Lc;
    int n;
 
    printf("头插法建La：输入个数及各元素(请按降序输入，这样La为升序): ");
    scanf("%d", &n);
    CreateList_H(&La, n);
 
    printf("尾插法建Lb：输入个数及各元素(请按升序输入，这样Lb为升序): ");
    scanf("%d", &n);
    CreateList_T(&Lb, n);
 
    printf("La = "); ListTraverse(La);
    printf("Lb = "); ListTraverse(Lb);
 
    MergeList_L(&La, &Lb, &Lc);
    printf("(1)  合并后 Lc = "); ListTraverse(Lc);
 
    DeleteDuplicates(Lc);
    printf("(2)  去重后Lc = "); ListTraverse(Lc);
 
    ReverseList(Lc);
    printf("(3)  逆置后Lc = "); ListTraverse(Lc);
 
    DestroyList(&Lc);
    return 0;
}