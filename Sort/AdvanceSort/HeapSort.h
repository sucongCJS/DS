#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <iostream>
#include "../../Heap/Heap.h"

using namespace std;

template<typename T>
void heapSort1(T arr[], int n){
    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for(int i=0; i<n; i++)
        maxheap.insert(arr[i]);
    

    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extracMax();
}

// heapify
template<typename T>
void heapSort2(T arr[], int n){
    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    for(int i=n-1; i>=0; i--)
        arr[i] = maxheap.extracMax();
}

template<typename T>
void __shiftDown(T arr[], int n, int k){
    while(k*2+1 < n){ // 从0开始的话, 左孩子有1的偏移量, 要+1, 同时取不到n
        int j = k*2+1; // arr[j] 在最后是要和 arr[k] 交换的
        if(j+1 < n && arr[j+1] > arr[j])
            j++;
        if(arr[k] >= arr[j])
            break;
        swap(arr[k], arr[j]);
        k = j;
    }
}

// 原地堆排序 不使用Heap类了
template<typename T>
void heapSort(T arr[], int n){
    // heapify
    for(int i=(n-2)/2; i>=0; i--) // n-2是因为有两次偏移, 一次是最后一个结点, 一次是最后一个非叶子结点
        __shiftDown(arr, n, i);

    

    for(int i=n-1; i>0; i--){
        swap(arr[i], arr[0]);
        __shiftDown(arr, i, 0); // 只将前 i 个堆化
    }
}

#endif