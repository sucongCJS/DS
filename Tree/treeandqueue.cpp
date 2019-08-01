// 顺序二叉树
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define MAX_SIZE 100
typedef char TElemType;
typedef int Status;

typedef struct BiTNode{
    TElemType data;
    BiTNode * lchild, * rchild;
}*BiTree;

typedef struct QNode{
    BiTree data;
    QNode * next;
} * QueuePtr;

struct LinkQueue{
    QueuePtr front; // 队头指针, 它指向的节点存第一个数据
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

// 入队
Status EnQueue(LinkQueue &Q, BiTree e){
    QNode * p = new QNode;
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

// 出队 (要警惕只剩一个的情况)
Status DeQueue(LinkQueue &Q, BiTree &e){
    if(Q.front == Q.rear) return ERROR;
    QNode * p = Q.front->next;
    e = p->data;
    if(Q.front->next == Q.rear) Q.rear = Q.front;
    // 注意! 但只有一个元素时: Q.front->next指向最后一个元素的下一个, 也就是NULL; 但不止一个元素的时候:...
    Q.front->next = p->next;
    delete p;
    return OK;
}

// 按先序输入
void CreateBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if(ch == '#') T = NULL;
    else{
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

// 前序遍历
void PreOrderTraverse(BiTree T){
    if(T){
        cout<<T->data<<" ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 层次遍历二叉树, 统计度数为1的结点个数
int level(BiTree T){
    int num = 0;
    if(T){
        LinkQueue Q;
        InitQueue(Q);
        EnQueue(Q, T);
        BiTree p;
        while(!QueueEmpty(Q)){
            DeQueue(Q, p);
            cout<<p->data<<' ';
            if((p->lchild && !p->rchild) || (!p->lchild && p->rchild)) ++num;
            if(p->lchild) EnQueue(Q, p->lchild);
            if(p->rchild) EnQueue(Q, p->rchild);
        }
    }
    return num;
}

void LevelTraverse(BiTree T){
    if(T){
        LinkQueue Q;
        InitQueue(Q);
        EnQueue(Q, T);
        BiTree p;
        while(!QueueEmpty(Q)){
            DeQueue(Q, p);
            cout<<p->data<<' ';
            if(p->lchild) EnQueue(Q, p->lchild);
            if(p->rchild) EnQueue(Q, p->rchild);
        }
    }
}

int main(){
    BiTree T;
    CreateBiTree(T);
    // 测试用例: A B C # # D E # G # # F # # #
    // T = new BiTNode;
    // T->lchild = new BiTNode;
    // T->rchild = NULL;
    // T->data = 'A';
    // T->lchild->data = 'C';
    // // T->rchild->data = 'B';
    // T->lchild->lchild = NULL;
    // T->lchild->rchild = NULL;
    // // T->rchild->lchild = NULL;
    // // T->rchild->rchild = NULL;

    LevelTraverse(T);

    // cout<<"Pre:\t"; PreOrderTraverse(T);
    // cout<<endl;

    // int num = level(T);
    // cout<<endl<<num<<endl;

    return 0;
}