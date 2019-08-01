// 用循环链表表示队列 不带头结点,只有指向队尾的指针
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;

typedef struct QueueNode{
    QElemType data;
    QueueNode * next;
} * QueuePtr;

struct LinkQueue{
    QueuePtr rear; // Q.rear存数据 头结点(Q.rear->next)指向的不存数据
};

Status InitQueue(LinkQueue &Q){
    // Q.rear->next 相当于Q.front
    Q.rear->next->next = Q.rear = Q.rear->next = new QueueNode;
    return OK;
}


Status DestroyQueue(LinkQueue &Q){
    QueueNode * s;
    while(Q.rear != Q.rear->next){
        s = Q.rear->next;
        Q.rear->next = s->next;
        delete s;
    }

}

// 判断队空
bool QueueEmpty(LinkQueue Q){
    // 头结点的next指针指向自己的时候队空
    // 空的时候Q.rear指向头结点
    return Q.rear->next->next == Q.rear->next;
}

Status EnQueue(LinkQueue &Q, QElemType e){
    QueueNode * p = new QueueNode;
    p->data = e;
    // p->next指向头节点
    p->next = Q.rear->next;
    // 将原来的最后一个的next指针指向p, 即p置于队尾
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e){
    if(Q.rear->next->next == Q.rear->next) return ERROR;
    QueueNode * p = new QueueNode;
    p = Q.rear->next->next;
    e = p->data;

    // 以下两个的顺序不能颠倒
    Q.rear->next->next = p->next;
    // 当队列只有一个结点的时候, 队尾指针指向头结点
    if(Q.rear->next->next == Q.rear) Q.rear = Q.rear->next;

    delete p;
    return OK;
}

int main(){
    LinkQueue Q;
    InitQueue(Q);

    QElemType e = 100;
    EnQueue(Q, e);
    cout<<QueueEmpty(Q)<<endl;
    int a = 0;
    DeQueue(Q, a);
    cout<<a;
    cout<<QueueEmpty(Q)<<endl;
    e = 200;
    EnQueue(Q, e);
    cout<<QueueEmpty(Q)<<endl;
    InitQueue(Q);
    cout<<QueueEmpty(Q)<<endl;
}