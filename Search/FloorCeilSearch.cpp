#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

// 二分查找法, 在有序数组arr中, 查找target
// 如果找到target, 返回第一个target相应的索引index
// 如果没有找到target, 返回比target小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
// 如果这个target比整个数组的最小元素值还要小, 则不存在这个target的floor值, 返回-1
template<typename T>
int floor2(T arr[], int n, T target){
    int l = 0, r = n-1;
    while(l <= r){
        int mid = (r-l)/2 + l; // 防止溢出
        if(target == arr[mid]){
            while(arr[mid-1] == target)
                mid--;
            return mid;
        }
        else if(target > arr[mid])
            l = mid + 1;
        else
            r = mid - 1;
    }
    return -1;
}

// 测试我们用二分查找法实现的floor和ceil两个函数
// 请仔细观察在我们的测试用例中，有若干的重复元素，对于这些重复元素，floor和ceil计算结果的区别：）
int main(){
    int a[] = {1, 1, 1, 2, 2, 2, 2, 2, 4, 4, 5, 5, 5, 6, 6, 6};
    int n = sizeof(a)/sizeof(int);
    for( int i = 0 ; i <= 8 ; i ++ ){
        int floorIndex = floor(a, n, i);
        cout<<"the floor index of "<<i<<" is "<<floorIndex<<".";
        if( floorIndex >= 0 && floorIndex < n )
            cout<<"The value is "<<a[floorIndex]<<".";
        cout<<endl;

        // int ceilIndex = ceil(a, sizeof(a)/sizeof(int), i);
        // cout<<"the ceil index of "<<i<<" is "<<ceilIndex<<".";
        // if( ceilIndex >= 0 && ceilIndex < n )
        //     cout<<"The value is "<<a[ceilIndex]<<".";
        // cout<<endl;

        // cout<<endl;
    }

    return 0;
}