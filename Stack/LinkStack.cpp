// 链栈
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define OVERFLOW -2;
#define MAX 100
typedef int SElemType;
typedef int Status;

typedef struct StackNode{
    SElemType data;
    StackNode * next;
} * LinkStack;

Status InitStack(LinkStack &S){
    S = NULL;
    return OK;
}

bool StackEmpty(LinkStack S){
    return S == NULL;
}
// S是指向栈顶的指针, 将e入栈, 并移动栈顶指针
Status Push(LinkStack &S, SElemType e){
    StackNode * p = new StackNode;
    p->data = e;
    p->next = S;
    S = p;
    return OK;
}

Status Pop(LinkStack &S, SElemType &e){
    if(S == NULL) return ERROR;
    e = S->data;
    StackNode * p = S;
    S = S->next;
    delete p;
    return OK;
}

void ShowStack(LinkStack S){
    while(S!=NULL){
        cout<<S->data<<" ";
        S = S->next;
    }
    cout<<endl;
}

// Decimal to Octal 只能处理非负数
void conversion(){
    LinkStack S;
    int N;
    InitStack(S);
    cout<<"Enter a non-negative decimal number: ";
    cin>>N;
    while(N){
        Push(S, N%8);
        N = N/8;
    }
    cout<<"Equal to octal number: ";
    int e;
    if(StackEmpty(S)){
        cout<<"0";
        return;
    }
    while(!StackEmpty(S)){
        Pop(S, e);
        cout<<e;
    }
}

// 表达式求值
OperandType

int main(){
    LinkStack S; int e;
    InitStack(S);

    conversion(); // 十进制转八进制
    // ShowStack(S); // 打印栈
    // Push(S, 10); // 压栈
    // ShowStack(S); // 打印栈
    // Push(S, 11); // 弹栈
    // ShowStack(S); // 打印栈
    // Pop(S, e); // 弹栈
    // Pop(S, e); // 弹栈
    // ShowStack(S); // 打印栈
    // Push(S, 66); // 压栈
    // Push(S, 88); // 压栈
    // ShowStack(S); // 打印栈
}