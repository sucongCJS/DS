//
// Create by Jason Chen on 8/1/2019
//

#ifndef SELECTIONSORT_SORTTESTHELPER_H
#define SELECTIONSORT_SORTTESTHELPER_H

#include <iostream>
#include <ctime>
#include <cassert>

using namespace std;

namespace SortTestHelper{
    // 生成有n个元素的随机数组,每个元素的随机范围为[range_l, range_r]
    int* generateRandomArray(int n, int range_l, int range_r){
        assert(range_l <= range_r);
        int* arr = new int[n];
        srand(time(NULL)); // 随机种子

        for(int i=0; i<n; i++)
            arr[i] = rand() % (range_r - range_l + 1) + range_l;

        return arr;
    }

    // 生成一个几乎有序的随机数组
    // swapTimes == 0 时, 数组完全有序
    // swapTimes 越大, 数组越趋向于无序
    int* generateNearlyOrderedArray(int n, int swapTime){
        int* arr = new int[n];
        for(int i=0; i<n; i++)
            arr[i] = i;

        srand(time(NULL));
        for(int i=0; i<swapTime; i++){
            int posx = rand()%n; // [0,n)
            int posy = rand()%n;
            swap(arr[posx], arr[posy]);
        }

        return arr;
    }

    // 遍历数组
    template<typename T>
    void printArray(T arr[], int n){
        for(int i=0 ; i<n ; i++)
            cout<<arr[i]<<" ";
        cout<<endl;
        return;
    }

    // 检测排序结果
    template<typename T>
    bool isSorted(T arr[], int n){
        for(int i=0; i<n-1; i++)
            if(arr[i+1] < arr[i])
                return false;
        return true;
    }

    // 测试性能
    template<typename T>
    void testSort(string sortName, void(*sort)(T[], int), T arr[], int n){
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout<<sortName<<": "<<double(endTime - startTime) / CLOCKS_PER_SEC<<" s"<<endl;

        return;
    }

    // 复制数组
    template<typename T>
    T* copyArray(T arr[], int n){
        T* new_arr = new T[n];
        copy(arr, arr+n, new_arr);
        return new_arr;
    }
} // namespace SortTestSpace


#endif // SELECTIONSORT_SORTTESTHELPER_H