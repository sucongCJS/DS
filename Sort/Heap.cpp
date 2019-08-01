// 推排序 升序(用大顶堆)
// https://www.bilibili.com/video/av47196993
#include <iostream>
using namespace std;

// 获得堆结构  输入存储在一维数组中的树, 结点个数, 要对哪个数做处理
void Swap(int tree[], int i, int j){
    int tmp = tree[j];
    tree[j] = tree[i];
    tree[i] = tmp;
}
// 变成大顶堆(每个结点的值都大于或等于其左右孩子结点的值)
void Heapify(int tree[], int n, int i){
    // 如果i超出索引范围, 结束
    if(i >= n){
        return ;
    }
    int c1 = 2 * i + 1; // 第一个子节点
    int c2 = 2 * i + 2; // 第二个子节点
    // 取三个中最大的
    int max = i;
    if(c1 < n && tree[c1] > tree[max]) max = c1;
    if(c2 < n && tree[c2] > tree[max]) max = c2;
    // 如果最大的不是i, 交换
    if(max != i){
        Swap(tree, max, i);
        // 需要对原来max所在的 "三个结点的小树" 进行 "堆化"
        Heapify(tree, n, max);
    }
}
// 从最后一个非叶子结点开始
void BuildHeap(int tree[], int n){
    int last = n-1;
    int parent = (last-1)/2;
    for(int i=parent; i>=0; --i){
        Heapify(tree, n, i);
    }
}

// 升序排序
void HeapSort(int tree[], int n){
    BuildHeap(tree, n); // 构造大顶堆
    for(int i=n-1; i>=0; --i){
        Swap(tree, i, 0); // 将最后一个结点和根结点交换, 使得最后一个结点是最大的那个
        Heapify(tree, i, 0); // 把剩下的i个给堆化
    }
}

int main(){
    // int tree[] = {4,10,3,5,1,2};
    int tree[] = {2,5,3,1,10,4};
    // int tree[] = {45,7,6254,465,1,-12,0,3};
    int n = sizeof(tree)/sizeof(tree[0]);

    HeapSort(tree, n);

    for(int i=0; i<n; ++i){
        cout<<tree[i]<<" ";
    }
}