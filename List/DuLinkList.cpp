// 双向循环链表 带头结点
#include <iostream>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

using namespace std;

typedef struct DuLNode{
    ElemType data;
    DuLNode * prior;
    DuLNode * next;
} * DuLinkList;

// ??在第i个位置之前插入元素e
Status ListInsert_DuL(DuLinkList L, int i, ElemType e){
    DuLNode * p = L->next;
    int j=1;
    while((p!=L) && (j<i)){ // 将p定位到第i个元素
        p = p->next;
        ++j;
    }
    if((p==L) || (i<j)) return ERROR; // i太大或i太小
    DuLNode * s = new DuLNode;
    s->data = e;
    s->next = p;
    s->prior = p->prior;
    p->prior->next = s;
    p->prior = s;
    return OK;
}

// ??删除第i个元素
Status ListDelete_DuL(DuLinkList L, int i, ElemType &e){
    DuLNode * p = L->next;
    int j=1;
    while((p!=L) && (j<i)){ // 将p定位到第i个元素
        p = p->next;
        ++j;
    }
    if((p==L) || (i<j)) return ERROR; // i太大或i太小
    e = p->data;
    p->prior->next = p->next;
    p->next->prior = p->prior;
    delete p;
    return OK;
}



int main(){

}