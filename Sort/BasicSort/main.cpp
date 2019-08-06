#include <iostream>
#include "../SortTestHelper.h"

using namespace std;

template<typename T>
void selectionSort(T arr[], int n){
    for(int i=0; i<n; i++){
        int minIndex = i;
        for(int j=i+1; j<n; j++)
            if(arr[j] < arr[minIndex])
                minIndex = j;
        swap(arr[i], arr[minIndex]);
    }
}

// 比选择排序快, 如果数组基本有序, 会更快, 有时甚至比O(nlogn)快
template<typename T>
void insertionSort(T arr[], int n){
    for(int i=1; i<n; i++){
        T e = arr[i];
        int j; // 保存e应该插入的位置
        for(j=i; j>0 && e < arr[j-1]; j--){ // 提前终止循环
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
}

int main(){
    int n = 50000;
    // int* arr = SortTestHelper::generateRandomArray(n, 0, 3);
    int* arr = SortTestHelper::generateNearlyOrderedArray(n, 100);
    int* arr2 = SortTestHelper::copyArray(arr, n);

    // SortTestHelper::printArray(arr, n);
    SortTestHelper::testSort("Selection Sort", selectionSort, arr, n);
    SortTestHelper::testSort("Inserttion Sort", insertionSort, arr2, n);

    delete[] arr;
    delete[] arr2;
 
    return 0;
}