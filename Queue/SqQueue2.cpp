// 循环队列, 顺序存储, 以tag == 0和tag == 1来区别在队头指针(front)和队尾指针(rear)相等时，队列状态为“空”还是“满”
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define MAXQSIZE 3 // 队列的最大长度
#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;

// 队列的三种状态:
// 1. 空 tag == 0
// 2. 有数据但不满 tag == 1 && front != rear;
// 3. 满 tag == 1 && front == rear;

struct SqQueue{
    QElemType * base; // 用于动态分配内存空间
    int front; // 队头索引 front存数据
    int rear; // 队尾索引 rear不存数据
    int tag;
};

Status InitQueue(SqQueue &Q){
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) return ERROR;
    Q.front = Q.rear = 0;
    Q.tag = 0;
    return OK;
}

int QueueLength(SqQueue Q){
    if(Q.tag == 0) return 0;
    if(Q.front == Q.rear) return MAXQSIZE;

    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

// 入队
Status EnQueue(SqQueue &Q, QElemType e){
    // 队满
    if(Q.tag == 1 && Q.front == Q.rear) return ERROR;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear+1)%MAXQSIZE;

    if(Q.tag == 0) Q.tag = 1;
    
    return OK;
}

// 出队
Status DeQueue(SqQueue &Q, QElemType &e){
    if(Q.tag == 0) return ERROR;
    e = Q.base[Q.front];
    Q.front = (Q.front+1)%MAXQSIZE;

    if(Q.rear == Q.front) Q.tag = 0;

    return OK;
}

int main(){
    SqQueue q;
    InitQueue(q);
    cout<<QueueLength(q)<<endl;

    if(EnQueue(q, 100)) cout<<"Enqueu successfully"<<endl;
    else cout<<"Fail to enqueue"<<endl;
    // cout<<q.front<<", "<<q.rear<<endl;

    if(EnQueue(q, 200)) cout<<"Enqueu successfully"<<endl;
    else cout<<"Fail to enqueue"<<endl;
    // cout<<q.front<<", "<<q.rear<<endl;
    cout<<QueueLength(q)<<endl;

    if(EnQueue(q, 300)) cout<<"Enqueu successfully"<<endl;
    else cout<<"Fail to enqueue"<<endl;
    // cout<<q.front<<", "<<q.rear<<endl;

    if(EnQueue(q, 400)) cout<<"Enqueu successfully"<<endl;
    else cout<<"Fail to enqueue"<<endl;
    // cout<<q.front<<", "<<q.rear<<endl;
    
    cout<<QueueLength(q)<<endl;

    int a;
    DeQueue(q, a);
    cout<<q.front<<", "<<q.rear<<endl;
    cout<<QueueLength(q)<<endl;

    DeQueue(q, a);
    cout<<q.front<<", "<<q.rear<<endl;
    cout<<QueueLength(q)<<endl;
}