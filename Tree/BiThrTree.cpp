#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define MAX_SIZE 100
typedef char TElemType;

extern BiThrTree pre; // 指向前驱

typedef struct BiThrNode{
    TElemType data;
    BiThrNode * lchild, * rchild;
    unsigned char LTag, RTag;
    // LTag = 0, lchild指向左孩子
    // LTag = 1, lchild指向直接前驱
    // RTag = 0, rchild指向右孩子
    // RTag = 1, rchild指向直接后继
}BiThrNode, * BiThrTree;

// 中序线索化
void InThreading(BiThrTree p){
    if(p){
        InThreading(p->lchild);
        if(!p->lchild){
            p->LTag = 1;
            p->lchild = pre;
        }
        if(!pre->rchild){
            pre->RTag = 1;
            pre->rchild = p;
        }
        pre = p; // 保持pre指向p的前驱
        InThreading(p->rchild);
    }
}

// // 中序遍历二叉树T, 并将其中序线索化, Thrt指向头结点
// void InorderThreading(BiThrTree & Thrt, BiThrTree T){
//     Thrt = new BiThrNode;
//     Thrt->LTag = 0;
//     Thrt->RTag = 1;
//     Thrt->rchild = Thrt;
//     if(!T) 
// }



int main(){
    pre->rchild = NULL;
}