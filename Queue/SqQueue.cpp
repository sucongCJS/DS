// 循环队列 顺序存储 少用一个元素空间来区分队空队满
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define M 10 // 队列的最大长度
#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;

struct SqQueue{
    QElemType * base; // 用于动态分配内存空间
    int front; // 队头索引 front存数据
    int rear; // 队尾索引 rear不存数据
};

Status InitQueue(SqQueue &Q){
    Q.base = new QElemType[M];
    if(!Q.base) return ERROR;
    Q.front = Q.rear = 0;
    return OK;
}

int QueueLength(SqQueue Q){
    return (Q.rear - Q.front + M) % M;
}

// 入队
Status EnQueue(SqQueue &Q, QElemType e){
    if((Q.rear+1)%M == Q.front) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1)%M;
    return OK;
}

// 出队
Status DeQueue(SqQueue &Q, QElemType &e){
    if(Q.rear == Q.front) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%M;
    return OK;
}

// 从队头入队
Status EnQueueFront(SqQueue &Q, QElemType e){
    if((Q.front-1+M)%M == Q.rear) return ERROR;
    Q.front = (Q.front-1+M)%M;
    Q.base[Q.front] = e;
    return OK;
}

// 从队尾出队
Status DeQueueRear(SqQueue &Q, QElemType &e){
    if(Q.rear == Q.front) return ERROR;
    Q.rear = (Q.rear-1+M)%M;
    e = Q.base[Q.rear];
    return OK;
}

void DisplayQueue(SqQueue Q){
    int i = Q.front;
    while(i != Q.rear){
        cout<<Q.base[i]<<" ";
        i = (i+1)%M;
    }
}

int main(){
    SqQueue q;
    InitQueue(q);
    int a;
    // cout<<QueueLength(q)<<endl;

    EnQueue(q, 100);
    EnQueue(q, 200);
    EnQueue(q, 300);
    EnQueue(q, 400);
    DisplayQueue(q); cout<<endl;

    DeQueue(q, a);
    DisplayQueue(q); cout<<endl;

    EnQueueFront(q, 123);
    DisplayQueue(q); cout<<endl;

    EnQueueFront(q, 345);
    DisplayQueue(q); cout<<endl;

    DeQueueRear(q, a);
    DisplayQueue(q); cout<<endl;

    DeQueueRear(q, a);
    DisplayQueue(q); cout<<endl;
}