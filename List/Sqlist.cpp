// 顺序表
#include <iostream>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

using namespace std;

typedef struct{
    ElemType *elem;
    int length;
}SqList;

Status InitList(SqList &L){
    L.elem = new ElemType[MAXSIZE];
    L.length = 0;
    return OK;
}

void DestroyList(SqList &L){
    if(L.elem) delete[] L.elem;
    L.length=0;
    L.elem=NULL;
}

int GetLength(SqList L){
    return L.length;
}

bool ListEmpty(SqList L){
    if (L.length==0) return true;
    else return false;
}

void ClearList(SqList &L){
    L.length=0;
}

// i为位置
Status ListInsert(SqList &L, int i,ElemType e){
    if(i<1 || i>L.length+1) return ERROR;
    if(L.length==MAXSIZE) return ERROR;
    for(int j=L.length-1; j>=i-1; j--){
        L.elem[j+1]=L.elem[j];
    }
    L.elem[i-1]=e;
    ++L.length;
    return OK;
}

// i为位置, 返回i位置的值给e
Status GetElem(SqList L, int i, ElemType &e){
    if(i<1||i>L.length) return ERROR;
    e=L.elem[i-1]; return OK;
}

Status ListDelete(SqList &L, int i){
    if(i<1||i>L.length) return ERROR;
    for(int j=i; j<=L.length-1; j++){
        L.elem[j-1]=L.elem[j];
    }
    --L.length;
    return OK;
}

void DisplayList(SqList L){
    for(int i=0; i<=L.length-1; i++){
        cout<<L.elem[i]<<" ";
    }
    cout<<endl;
}

void ShowList(SqList L, int i){
    if(i<1||i>L.length){
        cout<<"Index error"<<endl;
    }
    else{
        cout<<"No."<<i<<" elem is "<<L.elem[i-1]<<endl;
    }
}

void ShowListBefore(SqList L, int i){
    if(i<1||i>L.length){
        cout<<"Index error"<<endl;
    }
    else{
        if(i==1){
            cout<<"No front"<<endl;
        }
        else{
            cout<<"No."<<i<<" elem's front is "<<L.elem[i-2]<<endl;
        }
    }
}

void ShowListAfter(SqList L, int i)
{
    if(i<1||i>L.length){
        cout<<"Index error"<<endl;
    }
    else{
        if(i==L.length){
            cout<<"No after"<<endl;
        }
        else{
            cout<<"No. "<<i<<" elem's after is "<<L.elem[i]<<endl;
        }
    }
}

// ??La, Lb为有序的, 合并到Lc
void MergeList(SqList La, SqList Lb, SqList &Lc){
    InitList(Lc);
    int ai=1, bi=1, ci=0; // 分别指向三个数组的位置, 不是索引
    int La_len = La.length;
    int Lb_len = Lb.length;
    ElemType av, bv; // 存储a, b比较到的值
    while(ai<=La_len && bi<=Lb_len){
        GetElem(La, ai, av);
        GetElem(Lb, bi, bv);
        if(av <= bv){
            ListInsert(Lc, ++ci, av);
            ai++;
        }else{
            ListInsert(Lc, ++ci, bv);
            bi++;
        }
    }
    while(ai<=La_len){
        GetElem(La, ai++, av);
        ListInsert(Lc, ++ci, av);
    }
    while(bi<=Lb_len){
        GetElem(Lb, bi++, bv);
        ListInsert(Lc, ++ci, bv);
    }
}

void ShowHelp(){
    cout<<"1----清空线性表"<<endl;
    cout<<"2----判断线性表是否为空"<<endl;
    cout<<"3----求线性表长度"<<endl;
    cout<<"4----获取线性表指定位置元素"<<endl;
    cout<<"5----��ǰ��"<<endl;
    cout<<"6----����"<<endl;
    cout<<"7----�����Ա�ָ��λ�ò���Ԫ��"<<endl;
    cout<<"8----ɾ�����Ա�ָ��λ��Ԫ��"<<endl;
    cout<<"9----��ʾ���Ա�"<<endl;
    cout<<"     �˳������һ��������"<<endl;
}

int main(){
    int OperateCode;
    ShowHelp();
    SqList L;
    InitList(L);
    while(1){
        cout<<"Input the Operate Code";
        cin>>OperateCode;
        if(OperateCode==1){
            ClearList(L);
            cout<<"Clear successfully\n";
        }
        
        else if(OperateCode==2){
            if(ListEmpty(L)){
                cout<<"Empty\n";
            }
            else{
                cout<<"Not empty\n";
            }
            
        }
        
        else if(OperateCode==3){
            cout<<"The length of list is :"<<GetLength(L)<<endl;
        }
        
        else if(OperateCode==4){
            int i;
            cout<<"Input the index: ";
            cin>>i;
            ShowList(L, i);
        }
        
        else if(OperateCode==5){
            int i;
            cout<<"Input the index: ";
            cin>>i;
            ShowListBefore(L, i);
        }
        
        else if(OperateCode==6){
            int i;
            cout<<"Input the index: ";
            cin>>i;
            ShowListAfter(L, i);
        }
        
        else if(OperateCode==7){
            int e, i;
            cout<<"Input the element: ";
            cin>>e;
            cout<<"Input the index: ";
            cin>>i;
            int status = ListInsert(L, i, e);
            if(!status) cout<<"Fail to insert"<<endl;
            else cout<<"No."<<i<<" element is "<<e<<endl;
        }
        
        else if(OperateCode==8){
            int i;
            cout<<"Input the index:"<<endl;
            cin>>i;
            ListDelete(L, i); 
        }
        else if(OperateCode==9){
            DisplayList(L);
        }
        else if(OperateCode<0){
            break;
        }
        else{
            cout<<"Wrong operate code"<<endl;
            ShowHelp();
        }
    }
    DestroyList(L);
    return 0;
}
