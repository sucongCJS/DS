// 顺序栈 
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define MAX 100
typedef int SElemType;
typedef int Status;

struct SqStack{
    SElemType * base; // 指向的存数据
    SElemType * top; // 指向的不存数据
    int stackSize; // 当前已分配的存储空间
};

Status InitStack(SqStack &S){
    S.base = S.top = new SElemType[MAX];
    S.stackSize = MAX;
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

Status Push(SqStack &S, SElemType e){
    if(S.top - S.base == S.stackSize) return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop(SqStack &S, SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *--S.top; // --S.top; e = *S.top;
    return OK;
}

Status GetTop(SqStack &S, SElemType &e){
    if(S.top == S.base) return ERROR;
    e = *(S.top-1);
    return OK;
}

int main(){
    
}