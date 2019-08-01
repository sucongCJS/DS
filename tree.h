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