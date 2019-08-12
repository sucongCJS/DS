// 寻找arr数组中第k小的元素

#include <iostream>
#include <ctime>
#include <cassert>
#include <algorithm>
#include "../TestHelper.h"

using namespace std;

// 双路快排和三路快排的思想也能用在selection算法中 :)
template<typename T>
int __partition(T arr[], int l, int r){
    int p = rand()%(r-l+1) + l;
    swap(arr[p], arr[l]);

    int j = l; //[l+1...j] < p ; [lt+1..i) > p
    for(int i=l+1; i <= r; i++) 
        if(arr[i] < arr[l])
            swap(arr[++j], arr[i]);
    
    swap(arr[l], arr[j]); // 还是得交换, 因为这不一定是最后一次

    return j;
}

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

// 求出arr[l...r]范围里第k小的数
template<typename T>
T __selection(T arr[], int l, int r, int k){
    if(l == r)
        return arr[l];
    
    // partition之后, arr[p]的正确位置就在索引p上
    int p = __partition2(arr, l, r);
    if(p == k)
        return arr[p];
    else if(p < k)
        return __selection(arr, p+1, r, k);
    else
        return __selection(arr, l, p-1, k);
}

// k取值[0, n-1]
template<typename T>
T selection(T arr[], int n, int k){
    assert(k < n && k >= 0);

    srand(time(NULL));
    return __selection(arr, 0, n-1, k);
}

// k取值[1,n]
template<typename T>
T selection2(T arr[], int n, int k){
    return selection(arr, n, k-1);
}

// 测试 selection算法
int main() {

    // 生成一个大小为n, 包含0...n-1这n个元素的随机数组arr
    int n = 10000;
    int* arr = TestHelper::generateOrderedArray(n);
    TestHelper::shuffleArray(arr, n);

    // 验证selection算法, 对arr数组求第i小元素, 应该为i
    for( int i = 0 ; i < n ; i ++ ){
        assert( selection(arr, n, i) == i );
        cout<<"test "<<i<<" complete."<<endl;
    }
    cout<<"Test selection completed."<<endl;

    delete[] arr;

    cout << endl;

    // 验证selection2算法
    arr = TestHelper::generateOrderedArray(n);
    TestHelper::shuffleArray(arr, n);

    // 对arr数组求第i小元素, 应该为i - 1 (在selection2中, 第k小元素的k是从1索引的)
    for( int i = 1 ; i <= n ; i ++ ){
        assert( selection2(arr, n, i) == i - 1 );
        cout<<"test "<<i<<" complete."<<endl;
    }
    cout<<"Test selection2 completed."<<endl;

    delete[] arr;

    return 0;
}