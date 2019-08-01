// 二叉排序树 即 二叉搜索树
// 部分代码逻辑与 `Tree/BStree.cpp` 相同
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

struct BSNode{
    ElemType data;
    BSNode * rchild;
    BSNode * lchild;
};

// 只存储根节点
struct BSTree{
    BSNode * root;
};

// 插入成二叉搜索树
void CreateBST(BSTree * T, ElemType value){
    BSNode * N = new BSNode;
    N->data = value;
    N->lchild = NULL;
    N->rchild = NULL;
    // 新树, 直接做根
    if(T->root == NULL){
        T->root = N;
        return ;
    }
    else{
        BSNode * tp = T->root;
        while(tp){
            // 小于根 走左边
            if(value < tp->data){
                if(tp->lchild) tp = tp->lchild;
                else{
                    tp->lchild = N;
                    return ;
                }
            }
            // 大于根 走右边
            else{
                if(tp->rchild) tp = tp->rchild;
                else{
                    tp->rchild = N;
                    return ;
                }
            }
            
        }
    }
}
// 中序遍历
void Inorder(BSNode * N){
    if(N != NULL){
        Inorder(N->lchild);
        cout<<N->data<<" ";
        Inorder(N->rchild);
    }
}
// 查找元素有有序数组中的位置 
// ??找到后还是会执行完整个中序遍历
static int loc = 0;
void Find(BSNode * N, ElemType tgt){
    if(N != NULL){
        Find(N->lchild, tgt);
        loc++;
        if(N->data == tgt){
            cout<<loc;
        }
        Find(N->rchild, tgt);
    }
}

static int time = 0; // 查找次数
BSNode * SearchBST(BSNode * N, ElemType key){
    if(key == N->data){
        return N;
    }else if(key < N->data){
        time++;
        if(!N->lchild) return NULL;
        return SearchBST(N->lchild, key);
    }else{
        time++;
        if(!N->rchild) return NULL;
        return SearchBST(N->rchild, key);
    }
}  

int main(){
    int arr[] = {6, 3, 8, 2, 5, 1, 7, 19, 10};
    int len = sizeof(arr)/sizeof(arr[0]);
    BSTree T;
    T.root = NULL;

    for(int i=0; i < len; i++){
        CreateBST(&T, arr[i]);
    }

    cout<<"After sorted:\t"; Inorder(T.root); cout<<endl;
    
    BSNode * p;
    int tgt = 7;
    p = SearchBST(T.root, tgt);
    cout<<"Find "<<tgt<<" for "<<time<<" times, and ";
    if(p == NULL){
        cout<<"fail to found";
    }else{
        cout<<"found "<<p->data<<" at ";
        Find(T.root, tgt); // 如果能找到, 查找目标的位置
    }
}