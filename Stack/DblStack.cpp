// Dual_Stack 双栈
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
typedef int SElemType;
typedef int Status;

struct DblStack{
    int top[2], bot[2];
    SElemType * V;
    int m;
};

Status InitStack(DblStack &S, int m){
    S.V = new SElemType[m];
    // 设置可容纳的最大个数
    S.m = m;
    if(!S.V) return ERROR;
    S.top[0] = -1;
    S.bot[0] = -1;
    S.top[1] = m;
    S.bot[1] = m;
    return OK;
}

// Both Left and Right Stack is Empty retuen 1, else return 0
Status IsEmpty(DblStack S){
    return (S.top[0] == S.bot[0]) && (S.top[1] == S.bot[1]);
}

Status IsFull(DblStack S){
    return S.top[1] - S.top[0] == 1;
}

// i=0 is Left Stack, i=1 is Right Stack
Status Push(DblStack &S, int i, SElemType e){
    if(IsFull(S)) return ERROR;

    switch(i){
        case 0: S.V[++S.top[0]] = e; return OK;
        case 1: S.V[--S.top[1]] = e; return OK;
        default: return ERROR;
    }
}

// i=0 is Left Stack, i=1 is Right Stack
Status Pop(DblStack &S, int i, SElemType &e){
    switch(i){
        case 0:
            if(S.top[0] == -1) return ERROR;
            else e = S.V[S.top[0]--]; return OK;
        case 1:
            if(S.top[1] == S.m) return ERROR;
            else e = S.V[S.top[1]++]; return OK;
        default: return ERROR;
    }
}

// SElemType Pop(DblStack &S, int i){
//     switch(i){
//         case 0: 
//             // cout<<S.V[S.top[0]--]<<endl;
//             if(S.top[0] == -1) cout<<"empty!!!\n"; return -1;
//             return S.V[S.top[0]--];
//         case 1:
//             return S.V[S.top[1]++];
//     }
//     return -1;
// }

int main(){
    DblStack S;
    InitStack(S, 10);
    // if(IsEmpty(S)) cout<<"Stack is empty\n";
    // else cout<<"Stack is not empty\n";


    if(Push(S, 0, 100)) cout<<"Push successfully\n";
    if(Push(S, 1, 200)) cout<<"Push successfully\n";
    if(Push(S, 123, 200)) cout<<"Push successfully\n";
    else cout<<"Push fail\n";

    // cout<<Pop(S, 0)<<endl;
    // cout<<Pop(S, 1)<<endl;

    int e;
    if(Pop(S, 0, e)) cout<<e<<endl;
    else cout<<"Pop ERROR\n";
    if(Pop(S, 1, e)) cout<<e<<endl;
    else cout<<"Pop ERROR\n";
    if(Pop(S, 1, e)) cout<<e<<endl;
    else cout<<"Pop ERROR\n";

    if(IsEmpty(S)) cout<<"Stack is empty\n";
    else cout<<"Stack is not empty\n";
}