#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include "InsertionSort.h"

using namespace std;

// 对arr[l..r]部分进行partition操作
// 返回p, 使得arr[l..p-1] < arr[p] < arr[p+1..r]
template<typename T>
int __partition(T arr[], int l, int r){
    swap(arr[l], arr[rand()%(r-l+1) + l]); 
    // 如果每次取第一个为标定点, 对于有序的数组, 快排会退化为O(n^2)的算法, 采用随机取标定点解决, 但最坏的时间复杂度还是不变, 只是概率非常低, <随机算法>
    T v = arr[l];

    // arr[l+1...j] < v, arr[j+1...i) > v, i是开区间因为arr[i]待考察, 还不确定大于还是小于
    int j = l;

    for(int i = l+1; i <= r; i++){
        if(arr[i] < v)
            swap(arr[++j], arr[i]);
    }
    swap(arr[l], arr[j]);

    return j;
}

// 对arr[l..r]部分进行快速排序
template<typename T>
void __quickSort(T arr[], int l, int r){
    if(r-l <= 35){
        insertionSort(arr, l, r);
        return;
    }

    int p = __partition(arr, l, r);
    __quickSort(arr, l, p-1);
    __quickSort(arr, p+1, r);
}

template<typename T>
void quickSort(T arr[], int n){
    srand(time(NULL));
    __quickSort(arr, 0, n-1);
}


////// 针对有大量重复值的数组进行优化
template<typename T>
int __partition2(T arr[], int l, int r){
    swap(arr[l], arr[rand()%(r-l+1) + l]);
    T v = arr[l];
    // 这样做的好处??
    int i = l+1, j = r;
    while(true){
        while(i <= r && arr[i] < v) i++; // 要判断是否越界, 且得先判断是否越界 6, 6就会导致越界
        while(j >= l+1 && arr[j] > v) j--; // 两个while都没有等于 v 的, 等于 v 的会被分配在左右两边以保持树结构的平衡
        if(i > j)
            break;
        swap(arr[i++], arr[j--]);
    }
    swap(arr[l], arr[j]); 
    // i 最终停在了从前向后第一个大于等于v的元素
    // j 最终停在了从后向前第一个小于等于v的元素
    return j;
}

// 对arr[l..r]部分进行快速排序
template<typename T>
void __quickSort2(T arr[], int l, int r){
    if(r-l <= 35){
        insertionSort(arr, l, r);
        return;
    }

    int p = __partition2(arr, l, r);
    __quickSort2(arr, l, p-1);
    __quickSort2(arr, p+1, r);
}

template<typename T>
void quickSort2(T arr[], int n){
    srand(time(NULL));
    __quickSort2(arr, 0, n-1);
}


////////// 三路快排 arr[l..r]
// 将 arr 分为 arr[l+1..lt]<v, arr[lt+1..i-1]==v, arr[gt..r]>v
// 对于有大量重复元素的数组有 巨大 的优势
template<typename T>
void __quickSort3Ways(T arr[], int l, int r){
    if(r-l <= 25){
        insertionSort(arr, l, r);
        return;
    }

    // partition
    swap(arr[l], arr[rand()%(r-l+1) + l]);
    T v = arr[l];

    int lt = l; // arr[l+1..lt] < v 初始的时候要确保这个区间是空的
    int gt = r+1; // arr[gt..t] > v 空
    int i = l+1; // arr[lt+1..i) == v i还不确定, 所以开区间. 初始时这个区间也为空!
    while(i < gt){
        if(arr[i] == v)
            i++;
        else if(arr[i] < v)
            swap(arr[i++], arr[++lt]);
        else if(arr[i] > v)
            swap(arr[i], arr[--gt]);
    }
    swap(arr[l], arr[lt]);

    __quickSort3Ways(arr, l, lt-1); // 注意上面的交换
    __quickSort3Ways(arr, gt, r);
}

template<typename T>
void quickSort3Ways(T arr[], int n){
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n-1);
}

#endif