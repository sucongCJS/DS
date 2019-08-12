#ifndef MERGESORT_H
#define MERGESORT_H

#include <iostream>
#include "InsertionSort.h"

using namespace std;

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __merge(T arr[], int l, int mid, int r){
    // T aux[r-l+1]; // auxiliary
    T* aux = new T[r-l+1]; // VS不支持动态长度数组, 得用new申请空间, 删除空间
    // 原来数组的元素复制到辅助数组
    for(int i=l; i<=r; i++)
        aux[i-l] = arr[i];

    // 合并
    int i=0, j=mid-l+1; // 辅助数组上的
    for(int k=l; k<=r; k++){
        if(i > mid-l)
            arr[k] = aux[j++];
        else if(j > r-l)
            arr[k] = aux[i++];
        else if(aux[i] < aux[j]) // 等于的时候也不交换, 以保证稳定性
            arr[k] = aux[i++];
        else
            arr[k] = aux[j++];
    }

    delete[] aux;
}

// 递归使用归并排序, 对arr[l..r]的范围进行排序
template<typename T>
void __mergeSort(T arr[], int l, int r){
    // if(l >= r)
    //     return;
    if(r-l <= 25){ // 当数组长度很小的时候, 用插入会快一些, 毕竟数组几乎有序, 且O(n^2)只是在n很大的时候才大
        insertionSort(arr, l, r);
        return;
    }
    
    int mid = (l+r)/2; //??如果l+r溢出
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    if(arr[mid] > arr[mid+1]) // 如果数组几乎有序, 加了会更快
        __merge(arr, l, mid, r);
}

// 自上而下的归并
// 如果是链表就不能用啦, 只能应用于顺序存储的数组?
template<typename T>
void mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1); // 假装是私有函数
}

// ?? 对链表进行排序
// 自底向上的归并
template<typename T>
void mergeSortBU(T arr[], int n){
    int is = 16; // 使用插入排序的最小单位
    for(int i = 0; i < n; i += is) // 应该比 min里面 i 加的数应该大一位, 因为这是下一个部分的第一个
        insertionSort(arr, i, min(i + is - 1, n-1)); 

    for(int sz = is; sz < n; sz += sz){ // sz为一小个有序部分的长度, sz只要小于n就好了, 不用等于, 等于的时候已经没有第二个子数组了, sz从第is个开始, is个已经是有序的了
        for(int i = 0; i + sz < n; i += sz + sz) // 第二部分的 i+sz 必须小于 n, 第二部分才至少有一个值, 归并才有意义
            // 对 arr[i...i+sz-1] 和 arr[i+sz...i+sz+sz-1] 进行归并
            // 已经有序就跳过!
            if(arr[i + sz - 1] > arr[i + sz])
                __merge(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1)); // 剩下的不足sz个, 直接最后一个
    }
}

#endif //MERGESORT_H
