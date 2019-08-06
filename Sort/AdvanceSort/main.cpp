#include <iostream>
#include "../SortTestHelper.h"
#include "InsertionSort.h"

using namespace std;

// 将arr[l...mid]和arr[mid+1...r]两部分进行归并
template<typename T>
void __merge(T arr[], int l, int mid, int r){
    T aux[r-l+1]; // auxiliary
    // 原来数组的元素复制到辅助数组
    for(int i=l; i<=r; i++)
        aux[i-l] = arr[i];

    // 合并
    int i=l, j=mid+1;
    for(int k=l; k<=r; k++){
        if(i > mid){
            arr[k] = aux[j-l];
            j++;
        }
        else if(j > r){
            arr[k] = aux[i-l];
            i++;
        }
        else if(aux[i-l] < aux[j-l]){
            arr[k] = aux[i-l];
            i++;
        }
        else{
            arr[k] = aux[j-l];
            j++;
        }
    }
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

template<typename T>
void mergeSort(T arr[], int n){
    __mergeSort(arr, 0, n-1); // 假装是私有函数
}

int main(){
    int n=50000000;
    int* arr1 = SortTestHelper::generateNearlyOrderedArray(n, 10);
    int* arr2 = SortTestHelper::copyArray(arr1, n);

    SortTestHelper::testSort("Insertion Sort", insertionSort, arr1, n);
    SortTestHelper::testSort("Merge Sort", mergeSort, arr2, n);
    
    delete[] arr1;
    delete[] arr2;

    return 0;
}