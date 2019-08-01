// 线性表之单链表 带头结点
// bugs:
// - 插入两个值, 然后删除第一个, 打印链表时出错
// - 操作符输字母错
// - 插入值输字母错
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;


// 通常用LinkList定义某个的单链表的头指针, LNode *表示指向单链表任意节点的指针变量
typedef struct LNode{
    ElemType data;
    LNode * next;
}* LinkList;

Status InitList(LinkList &L){
    L = new LNode; // 指向头结点的指针, 即头指针
    // BTW: new运算根据类型来确定需要多少字节的内存, 然后找到这样的内存, 并返回其地址. L为LNode类型指针, 作为头指针, 现申请一个LNode类型的空间并将其地址存于头指针中, L指向头结点
    if(L == NULL) return ERROR;
    L->next = NULL;
    // 头结点数据域表示长度
    L->data = 0;
    return OK;
}

// ??头插法创建链表 O(1)
void CreateList_H(LinkList &L, int n){
    L = new LNode;
    L->next = NULL;
    for(int i=0; i<n; ++i){
        LNode * p = new LNode;
        cin>>p->data;
        p->next = L->next;
        L->next = p;
    }
}
// ??尾插法创建链表 O(1)
void CreateList_R(LinkList & L, int n){
    L = new LNode;
    L->next = NULL;
    LNode * rear = L;
    for(int i=0; i<n; ++i){
        LNode * p = new LNode;
        cin>>p->data;
        rear->next = p;
        p->next = NULL;
        rear = p;
    }
}

Status DestroyList(LinkList &L){
    LNode * p;
    while(L){
        p = L;
        L = L->next;
        delete p;
    }
    return OK;
}

// make e no.i's value
Status GetElem(LinkList L, int i, ElemType &e){
    LNode * p = L->next; // 初始化, p指向首元结点
    int j = 1;
    while(p && j<i){
        p = p->next;
        ++j;
    }
    // i > n or i <= 0
    if(!p || j>i) return ERROR;
    e = p->data;
    return OK;
}

// return the address of elem that value is e, return null if not found
LNode * LocateElem(LinkList L, ElemType e){
    LNode * p = L->next;
    while(p && p->data != e){
        p = p->next;
    }
    return p;
}

// insert elem e at i
Status ListInsert(LinkList &L, int i, ElemType e){ // 引用仅仅是因为可能要L->data
    // p不能指向首元结点, 不然链表为空的时候直接就退出了
    LNode * p = L;
    int j = 0;
    // 但i等于零或i为负数时都不需要while循环
    while(p && (j<i-1)){
        p = p->next;
        ++j;
    }
    if(!p || (j>i-1)) return ERROR;
    LNode * s = new LNode;
    s->data = e;
    s->next = p->next;
    p->next = s;
    // LinkList length +1
    L->data++;
    return OK;
}

Status ListDelete(LinkList &L, int i){
    // p最终要指向要删除的节点的前一个(因为指向要删除的那一个的话没办法修改前面的节点), 所以这里p指向头结点
    LNode * p = L;
    int j = 0;
    while((p->next) && (j<i-1)){
        p = p->next;
        ++j;
    }
    if(!(p->next) || (j>i-1)) return ERROR;
    LNode * tp = p;
    p->next = p->next->next;
    delete tp->next;
    // LNode * q = p->next;
    // p->next = q->next;
    // delete q;
    --L->data;
    return OK;
}

Status ClearList(LinkList L){
    LNode * p = L->next; 
    LNode * q;
    while(p){
        q = p;
        p = p->next;
        delete q;
        // q = p->next;
        // delete p;
        // p = q;
    }
    L->next = NULL;
    L->data = 0;
    return OK;
}

void DisplayList(LinkList L){
    LNode * p = L->next;
    while(p){
        cout<<p->data<<" ";
        p = p->next;
    }
}

int ListLength(LinkList L){
    return L->data;
    // LNode * p = L->next;
    // int len = 0;
    // while(p){
    //     ++len;
    //     p = p->next;
    // }
    // return len;
}

bool ListEmpty(LinkList L){
    return (L->next == NULL);
}

// 求前驱
void ShowListBefore(LinkList L, int i){
    if(i<1 || i>ListLength(L)){
        cout<<"Index error"<<endl;
    }
    else{
        if(i==1){
            cout<<"No front"<<endl;
        }
        else{
            LNode * p = L->next;
            --i;
            while(--i){
                p = p->next;
            }
            cout<<"Front is "<<p->data<<endl;
        }
    }
}

// 求后继
void ShowListAfter(LinkList L, int i){
    if(i<1 || i>ListLength(L)){
        cout<<"Index error"<<endl;
    }
    else{
        if(i==ListLength(L)){
            cout<<"No after"<<endl;
        }
        else{
            LNode * p = L->next;
            while(--i){
                p = p->next;
            }
            cout<<"After is "<<p->next->data<<endl;
        }
    }
}

// 将Lb合并到La变为Lc (La, Lb的数据元素值必须为非递减的) 合并完Lc也为非递减的
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc){
    LNode * pa = La->next;
    LNode * pb = Lb->next;
    LNode * pc;
    Lc = pc = La;

    while(pa && pb){
        // pc指向小的结点
        if(pa->data > pb->data){
            pc->next = pb;
            pb = pb->next;
        }
        else{
            pc->next = pa;
            pa = pa->next;
        }
        pc = pc->next;
    }
    pc->next = pa? pa:pb;
    // if(pa) pc->next = pa;
    // else pc->next = pb;

    delete Lb; // 释放Lb的头结点
}

// ??将两链表合并
void ListUnion(LinkList & La, LinkList Lb){
    int La_len = ListLength(La);
    int Lb_len = ListLength(Lb);
    ElemType e;
    for(int i=1; i<=Lb_len; ++i){
        GetElem(Lb, i, e);
        if(!LocateElem(La, e)){
            ListInsert(La, ++La_len, e); // 不存在就插到最后
        }
    }
}

void show_help(){
    cout<<"1----Clear the List"<<endl;
    cout<<"2----Check if the list is empty"<<endl;
    cout<<"3----Get the length of the list"<<endl;
    cout<<"4----Get the element of the list"<<endl;
    cout<<"5----Show front element"<<endl;
    cout<<"6----Show after element"<<endl;
    cout<<"7----Insert element to the list"<<endl;
    cout<<"8----Delete element from the list"<<endl;
    cout<<"9----Display the list"<<endl;
    cout<<"     Enter a negative number to exit"<<endl;
}


int main(){
    int operate_code;
    show_help();
    LinkList L;
    InitList(L);
    while(1){
        cout<<"Please enter the operation code: ";
        cin>>operate_code;
        if(operate_code==1){
            if(ClearList(L)) cout<<"Successfully clear\n";
            else cout<<"Fail to clear\n";
        }
        else if(operate_code==2){
            if(ListEmpty(L)) cout<<"List is empty\n";
            else cout<<"List is not empty\n";
        }
        else if(operate_code==3){
            cout<<ListLength(L)<<endl;
        }
        else if(operate_code==4){
            int e;
            cout<<"Input the value of the element: ";
            cin>>e;
            cout<<"The address of "<<e<<" is "<<LocateElem(L, e)<<endl;
        }
        else if(operate_code==5){
            int i;
            cout<<"Input the location of the element: ";
            cin>>i;
            ShowListBefore(L, i);
        }
        else if(operate_code==6){
            int i;
            cout<<"Input the location of the element: ";
            cin>>i;
            ShowListAfter(L, i);
        }
        else if(operate_code==7){
            int e, i;
            cout<<"Input the value of the element: ";
            cin>>e;
            cout<<"Input the location of the element: ";
            cin>>i;
            if(ListInsert(L, i, e)) cout<<"Successfully insert"<<endl;
            else cout<<"Fail to insert"<<endl;
        }
        else if(operate_code==8){
            int i;
            cout<<"Input the location of the element: ";
            cin>>i;
            if(ListDelete(L, i)) cout<<"Successfully delete"<<endl;
            else cout<<"Fail to delete"<<endl;
        }
        else if(operate_code==9){
            DisplayList(L);
            cout<<endl;
        }
        else if(operate_code<0){
            break;
        }
        else{
            cout<<"\nWrong operate code"<<endl;
        }
        show_help();
    }
    // 销毁线性表
    DestroyList(L);
    return 0;

    // LinkList La, Lb, Lc;
    // InitList(La);
    // InitList(Lb);
    // InitList(Lc);

    // ListInsert(La, 1, 3);
    // ListInsert(La, 2, 5);
    // ListInsert(La, 3, 8);
    // ListInsert(La, 4, 11);
    // DisplayList(La);
    // cout<<endl;

    // ListInsert(Lb, 1, 2);
    // ListInsert(Lb, 2, 6);
    // ListInsert(Lb, 3, 8);
    // ListInsert(Lb, 4, 9);
    // ListInsert(Lb, 5, 11);
    // DisplayList(Lb);
    // cout<<endl;

    // MergeList_L(La, Lb, Lc);
    // DisplayList(Lc);
}