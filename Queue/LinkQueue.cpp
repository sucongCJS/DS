// 链队列 带头结点
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;

typedef struct QNode{
    QElemType data;
    QNode * next;
} * QueuePtr;

struct LinkQueue{
    QueuePtr front; // 队头指针, 它指向的节点指向的下一个结点存数据
    QueuePtr rear; //队尾指针, 它所指的节点存数据
};

Status InitQueue(LinkQueue &Q){
    Q.front = Q.rear = new QNode;
    Q.front->next = NULL;
    return OK;
}

Status DestroyQueue(LinkQueue &Q){
    // 为空时删除头尾指针共同指向的那个节点
    while(Q.front){
        Q.rear = Q.front->next;
        delete Q.front;
        Q.front = Q.rear;
    }
    return OK;
}

bool QueueEmpty(LinkQueue Q){
    return Q.front == Q.rear;
}

Status GetHead(LinkQueue Q, QElemType &e){
    if(Q.front == Q.rear) return ERROR;
    e = Q.front->next->data;
    return OK;
}

// 入队
Status EnQueue(LinkQueue &Q, QElemType e){
    QNode * p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p; // 修改尾结点的指针, p做最后一个
    Q.rear = p; // 尾指针指向最后一个结点
    return OK;
}

// 出队 (要警惕只剩一个的情况)
Status DeQueue(LinkQueue &Q, QElemType &e){
    if(Q.front == Q.rear) return ERROR;
    QNode * p = Q.front->next;
    e = p->data;
    if(Q.front->next == Q.rear) Q.rear = Q.front; // 注意! 但只有一个元素时: Q.front->next指向最后一个元素的下一个, 也就是NULL; 但不止一个元素的时候:...
    Q.front->next = p->next;
    delete p;
    return OK;
}

void ShowQueue(LinkQueue Q){
    while(Q.front->next){
        Q.front = Q.front->next;
        cout<<Q.front->data<<" ";
    }
}

int main(){
    LinkQueue Q;
    InitQueue(Q);
    
    EnQueue(Q, 10); // 入队
    EnQueue(Q, 20); // 入队
    EnQueue(Q, 30); // 入队
    EnQueue(Q, 40); // 入队
    EnQueue(Q, 50); // 入队
    cout<<"Queue: "; ShowQueue(Q); cout<<endl; // 打印队列
    int e;
    cout<<"Head is: "; GetHead(Q, e); cout<<e<<endl; // 打印队头
    DeQueue(Q, e); // 出队
    cout<<"Queue: "; ShowQueue(Q); cout<<endl; // 打印队列
    DeQueue(Q, e); // 出队
    DeQueue(Q, e); // 出队
    DeQueue(Q, e); // 出队
    DeQueue(Q, e); // 出队
    DeQueue(Q, e); // 出队
    if(QueueEmpty(Q)) cout<<"Queue is Empty"<<endl;
    cout<<"Queue: "; ShowQueue(Q); // 打印队列
    DestroyQueue(Q);
}