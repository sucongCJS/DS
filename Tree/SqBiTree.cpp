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
// /////////////////////////////////////////////
struct SqStack{
    BiTree * base; // 指向的存数据
    BiTree * top; // 指向的不存数据
    int stackSize;
};
Status InitStack(SqStack &S){
    S.base = S.top = new BiTree[MAX_SIZE];
    S.stackSize = MAX_SIZE;
    return OK;
}
bool StackEmpty(SqStack S){
    return S.top == S.base;
}
int StackLength(SqStack S){
    // return (S.top - S.base + MAX)%MAX;
    return S.top - S.base;
}
Status ClearStack(SqStack &S){
    if(S.base) S.top = S.base;
    return OK;
}
Status DestroyStack(SqStack &S){
    if(S.base){
        delete[] S.base;
        S.stackSize = 0;
        S.base = S.top = NULL;
    }
    return OK;
}

Status Push(SqStack &S, BiTree e){
    if(S.top - S.base == S.stackSize) return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, BiTree &e){
    if(S.top == S.base) return ERROR;
    e = *--S.top; // --S.top; e = *S.top;
    return OK;
}
// /////////////////////////////////////////


// 前序遍历
void PreOrderTraverse(BiTree T){
    if(T){
        cout<<T->data<<" ";
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

// 中序遍历
void InOrderTraverse(BiTree T){
    if(T){
        InOrderTraverse(T->lchild);
        cout<<T->data<<" ";
        InOrderTraverse(T->rchild);
    }
}

// 中序遍历非递归算法
void InOrderTraverse2(BiTree T){
    SqStack S;
    InitStack(S);
    BiTree p = T;
    BiTree q;
    while(p || !StackEmpty(S)){
        if(p){
            Push(S, p);
            p = p->lchild; // 根指针进栈, 遍历左子树
        }
        else{
            Pop(S, q); // 没有左子树, 退栈
            cout<<q->data<<" "; // 访问根结点
            p = q->rchild; // 遍历右子树
        }
    }
}

// 后序遍历
void PostOrderTraverse(BiTree T){
    if(T){
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout<<T->data<<" ";
    }
}

// 按先序输入
void CreateBiTree(BiTree &T){
    char ch;
    cin>>ch;
    if(ch == '#') T = NULL; // 递归结束, 创建空树
    else{
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild); // 递归创建左子树
        CreateBiTree(T->rchild);
    }
}

// 计算二叉树结点总数
int NodeCount(BiTree T){
    if(T == NULL)
        return 0;
    return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

// 计算叶子结点
int LeafCount(BiTree T){
    if(T == NULL) // 空树
        return 0;
    if(T->lchild == NULL && T->rchild == NULL) // 叶子节点
        return 1;
    else return LeafCount(T->lchild) + LeafCount(T->rchild);
}

int Depth(BiTree T){
    if(T == NULL) return 0;
    else{
        int m = Depth(T->lchild);
        int n = Depth(T->rchild);
        return m > n? m+1:n+1;
    }
}

// 交换左右孩子
void ChangeLR(BiTree &T){
    BiTree tmp;
    if(T == NULL) return;
    else{
        tmp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = tmp;
    }
    ChangeLR(T->lchild);
    ChangeLR(T->rchild);
}

int main(){
    BiTree T;
    CreateBiTree(T);
    // 测试用例: A B C # # D E # G # # F # # #
    cout<<"Node number: "<<NodeCount(T)<<endl;
    cout<<"Leaf node number: "<<LeafCount(T)<<endl;

    cout<<"Pre: "; PreOrderTraverse(T);
    cout<<"\nIn: "; InOrderTraverse(T);
    cout<<"\nIn: "; InOrderTraverse2(T);
    cout<<"\nPost: "; PostOrderTraverse(T);

    cout<<"\nDepth: "<<Depth(T);

    ChangeLR(T);

    return 0;
}