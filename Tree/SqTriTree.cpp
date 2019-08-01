// 顺序二叉树
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define MAX_SIZE 100
typedef int TElemType;

typedef struct TriTNode{
    TElemType data;
    TriTNode * lchild, * rchild, * parent;
}*TriTree;

