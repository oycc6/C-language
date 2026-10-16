#include<stdio.h>
#include<stdlib.h>

/* ===================== 5. 一元多项式加法 ===================== */
typedef struct PNode{
    int coef;
    int exp;
    struct PNode *next;
} PNode, *Polynomial;

Polynomial CreatePoly(int n){
    Polynomial  head = (Polynomial)malloc(sizeof(PNode)) , r = head;
    head->next =NULL;
    for (int i=0; i<n; i++){
        Polynomial s =(Polynomial)malloc(sizeof(PNode));
        scanf("%d %d", &s->coef,&s->exp);
        s->next = NULL;
        r->next = s;
        r =s ;
    }
    return head;
}

void PrintPoly(Polynomial P){
    if (!P->next){ printf("0\n"); return;}
    for (Polynomial  p = P->next ;p;p=p->next){
        if (p != P ->next && p->coef >0) printf("+");
        printf("%d",p->coef);
        if (p->exp != 0) printf("x^%d",p->exp);
    }
    printf("\n");
}

Polynomial AddPoly(Polynomial Pa, Polynomial Pb){
    Polynomial pa = Pa->next,pb=Pb->next,pc =Pa, q;
    while (pa && pb){
        if (pa->exp <pb->exp){
            pc->next =pa;pc =pa;pa=pa->next;
        }else if (pa->exp > pb->exp){
            pc->next =pb;pc =pb;pb=pb->next;
        }else{
            int sum = pa->coef + pb->coef;
            if (sum != 0){
                pa->coef =sum;
                pc->next =pa;pc =pa;pa =pa->next;
            }else{
            q=pa;pa=pa->next;free(q);
            }
            q=pb;pb=pb->next;free(q);
        }
}
pc->next =pa?pa:pb;
free(Pb);
return Pa;
}


/* ===================== 6. 拆分单链表 ===================== */
typedef struct LNode {
    int data;
    struct LNode *next;
} LNode,*LinkList;

LinkList CreateList_T(int n){
    LinkList head = (LinkList)malloc(sizeof(LNode)), r = head;
    head->next = NULL;
    for (int i=0; i<n ;i++){
        LinkList s = (LinkList)malloc(sizeof(LNode));
        scanf("%d",&s->data);
        s->next = NULL;
        r->next = s;
        r = s;
    }
    return head;
}

void PrintList(LinkList L) {
    for (LinkList p= L->next; p; p =p->next)
    printf("%d ",p->data);
    printf("\n");
}

/* 原链表 L 不变：遍历 L，为每个结点“复制”一个新结点，按奇偶尾插到 La 或 Lb。
   尾插法保证相对顺序与 L 一致。时间 O(n) */
   void SplitList(LinkList L, LinkList *La,LinkList *Lb){
    *La = (LinkList)malloc(sizeof(LNode)); (*La)->next = NULL;
    *Lb = (LinkList)malloc(sizeof(LNode)); (*Lb)->next = NULL;
    LinkList ra = *La,rb = *Lb;
    for (LinkList p = L->next; p; p = p->next) {
        LinkList s = (LinkList)malloc(sizeof(LNode));
        s->data = p->data;
        s->next = NULL;
        if (p->data %2 !=0){
            ra->next =s;ra = s;}
        else{rb->next=s;rb=s; }
    }
 }

int main(void) {
    int n;
 
    printf("== 一元多项式加法 ==\n");
    printf("输入A(x)的项数及各项(系数 指数，指数升序): ");
    scanf("%d", &n);
    Polynomial A = CreatePoly(n);
    printf("输入B(x)的项数及各项: ");
    scanf("%d", &n);
    Polynomial B = CreatePoly(n);
    printf("A(x) = "); PrintPoly(A);
    printf("B(x) = "); PrintPoly(B);
    Polynomial C = AddPoly(A, B);
    printf("A+B  = "); PrintPoly(C);
 
    printf("\n== 拆分单链表 ==\n");
    printf("输入L的元素个数及各元素: ");
    scanf("%d", &n);
    LinkList L = CreateList_T(n), La, Lb;
    SplitList(L, &La, &Lb);
    printf("L  = "); PrintList(L);
    printf("La(奇数) = "); PrintList(La);
    printf("Lb(偶数) = "); PrintList(Lb);
    return 0;
}
 