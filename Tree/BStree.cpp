// Binary Search Tree 二叉搜索树
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

// 只存储根节点
struct Tree{
    Node * root;
};

// 插入成二叉搜索树
void insert(Tree * tree, ElemType value){
    Node * node = new Node;
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    // 新树, 直接做根
    if(tree->root == NULL){
        tree->root = node;
        return ;
    }
    else{
        Node * tp = tree->root;
        while(tp){
            // 小于根 走左边
            if(value < tp->data){
                if(tp->left) tp = tp->left;
                else{
                    tp->left = node;
                    return ;
                }
            }
            // 大于根 走右边
            else{
                if(tp->right) tp = tp->right;
                else{
                    tp->right = node;
                    return ;
                }
            }
            
        }
    }
}

// 前序遍历
void preorder(Node * node){
    if(node != NULL){
        cout<<node->data<<" ";
        preorder(node->left);
        preorder(node->right);
    }
}

// 中序遍历
void inorder(Node * node){
    if(node != NULL){
        inorder(node->left);
        cout<<node->data<<" ";
        inorder(node->right);
    }
}

// 后续遍历
void postorder(Node * node){
    if(node != NULL){
        postorder(node->left);
        postorder(node->right);
        cout<<node->data<<" ";
    }
}

// 获取树的深度
int get_height(Node * node){
    if(node == NULL){
        return 0;
    }
    int left_h = get_height(node->left);
    int right_h = get_height(node->right);
    int max = (left_h > right_h? left_h:right_h);
    return max + 1;
}

int main(){
    int arr[7] = {6, 3, 8, 2, 5, 1, 7};
    Tree tree;
    tree.root = NULL;

    for(int i=0; i < 7; i++){
        insert(&tree, arr[i]);
    }

    cout<<"front:\t"; preorder(tree.root); cout<<endl;
    cout<<"middle:\t"; inorder(tree.root); cout<<endl;
    cout<<"rear:\t"; postorder(tree.root); cout<<endl;
    
    cout<<get_height(tree.root);
    return 0;
}