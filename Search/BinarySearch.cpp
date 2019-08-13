// 二分查找
#include <iostream>
#include <ctime>
#include <cassert>
using namespace std;

// O(logn) 非递归
template<typename T>
int binarySearch(T arr[], int n, T target){
    // 在arr[l..r]之间查找
    int l = 0, r = n-1;
    while(l <= r){
        // int mid = (l + r) / 2;
        int mid = (r-l)/2 + l; // 防止溢出
        if(target == arr[mid])
            return mid;
        else if(target > arr[mid])
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// 递归
template<typename T>
int __binarySearch2(T arr[], int l, int r, T target){
    if(l > r)
        return -1;

    int mid = (r-l)/2 + l;
    if(target == arr[mid])
        return mid;
    else if(target > arr[mid])
        return __binarySearch2(arr, mid+1, r, target);
    else
        return __binarySearch2(arr, l, mid-1, target);
}

template<typename T>
int binarySearch2(T arr[], int n, T target){
    return __binarySearch2(arr, 0, n-1, target);
}



int main(){
    int n = 1000000;
    int* a = new int[n];
    for( int i = 0 ; i < n ; i ++ )
        a[i] = i;

    // 测试非递归二分查找法
    clock_t startTime = clock();

    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for( int i = 0 ; i < 2*n ; i ++ ){
        int v = binarySearch(a, n, i);
        if( i < n )
            assert( v == i );
        else
            assert( v == -1 );
    }
    clock_t endTime = clock();
    cout << "Binary Search (Without Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;


    // 测试递归的二分查找法
    startTime = clock();

    // 对于我们的待查找数组[0...N)
    // 对[0...N)区间的数值使用二分查找，最终结果应该就是数字本身
    // 对[N...2*N)区间的数值使用二分查找，因为这些数字不在arr中，结果为-1
    for( int i = 0 ; i < 2*n ; i ++ ){
        int v = binarySearch2(a, n, i);
        if( i < n )
            assert( v == i );
        else
            assert( v == -1 );
    }
    endTime = clock();
    cout << "Binary Search (Recursion): " << double(endTime - startTime) / CLOCKS_PER_SEC << " s"<<endl;

    delete[] a;

    return 0;
}