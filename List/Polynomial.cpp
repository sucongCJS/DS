// 多项式 链表
#include <iostream>
using namespace std;
#define OK 1
#define ERROR 0
typedef int Status;

typedef struct PNode{
    float coef; // 系数
    int expn; // 指数
    PNode * next;
} * Polynomial;

// ??输入项数
void CreatePolyn(Polynomial &P, int n){
    P = new PNode;
    P->next = NULL;
    for(int i=1; i<=n; ++i){
        PNode * s = new PNode;
        cin>>s->coef>>s->expn;
        PNode * pre = P; // 为q的前驱, 初始值为头结点
        PNode * q = P->next;
        // 找到第一个大于输入项指数的项*q
        while(q && (q->expn < P->expn)){
            pre = q;
            q = q->next;
        }
        s->next = q; // s->next = pre->next;
        pre->next = s;
    }
}