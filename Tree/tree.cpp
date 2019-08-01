#ifndef TREE_H
#define TREE_H
// 树 手动插入结点

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
typedef int ElemType;
typedef int Status;

struct Node{
    ElemType data;
    Node * right;
    Node * left;
};

// 前序遍历
void preorder(Node * n){
    if(n != NULL){
        cout<<n->data<<" ";
        preorder(n->left);
        preorder(n->right);
    }
}

// 中序遍历
void inorder(Node * n){
    if(n != NULL){
        inorder(n->left);
        cout<<n->data<<" ";
        inorder(n->right);
    }
}

// 后续遍历
void postorder(Node * n){
    if(n != NULL){
        postorder(n->left);
        postorder(n->right);
        cout<<n->data<<" ";
    }
}

// 所有结点的值都是正的
int get_maximum(Node * node){
    if(node == NULL){
        return -1;
    }
    else{
        int mx_l = get_maximum(node->left); // 左边最大
        int mx_r = get_maximum(node->right); // 右边最大
        int mid = node->data;
        // 返回三个中最大的那个
        return (mx_l > mx_r? (mx_l > mid? mx_l:mid):(mx_r > mid? mx_r:mid));
    }
}
#endif

int main(){
    Node n1, n2, n3, n4;
    n1.data = 5;
    n2.data = 6;
    n3.data = 7;
    n4.data = 8;

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = NULL;
    n3.left = NULL;
    n3.right = NULL;
    n4.left = NULL;
    n4.right = NULL;

    preorder(&n1);
    cout<<endl;
    inorder(&n1);
    cout<<endl;
    postorder(&n1);
    cout<<endl;

    cout<<get_maximum(&n1);
}