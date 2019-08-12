#include <iostream>
#include "../TestHelper.h"

using namespace std;

// 计算逆序数对的结果以long long返回
// 对于一个大小为N的数组, 其最大的逆序数对个数为 N*(N-1)/2, 非常容易产生整型溢出

// merge函数求出在arr[l...mid]和arr[mid+1...r]有序的基础上, arr[l...r]的逆序数对个数
long long __merge(int arr[], int l, int mid, int r){
    int* aux = new int[r-l+1];
    for(int i=l; i<=r; i++)
        aux[i-l] = arr[i];

    long long res = 0; // 初始化逆序数对个数 res = 0
    int i=0, j=mid-l+1; // 辅助数组上的

    for(int k=l; k<=r; k++){
        if(i > mid-l) // 如果左半部分元素已经全部处理完毕
            arr[k] = aux[j++];
        else if(j > r-l) 
            arr[k] = aux[i++];
        else if(aux[i] < aux[j])
            arr[k] = aux[i++];
        else{
            arr[k] = aux[j++];
            res += (long long)(mid - (i+l) + 1); // 右比左小, 此时当前元素和左边所有未处理的元素构成了逆序数对
        }
    }

    delete[] aux;

    return res;
}

// 求arr[l..r]范围的逆序数对个数
long long __inversionCount(int arr[], int l, int r){
    if(l >= r)
        return 0;
    
    int mid = (r - l) / 2 + l;
    long long resL = __inversionCount(arr, l, mid);
    long long resR = __inversionCount(arr, mid+1, r);

    return resL + resR + __merge(arr, l, mid, r);
}

long long inversionCount(int arr[], int n){
    return __inversionCount(arr, 0, n-1);
}



int main(){
    int n = 1000000;

    // 测试1: 测试随机数组
    cout<<"Test Inversion Count for Random Array, n = "<<n<<" :"<<endl;
    int* arr = TestHelper::generateRandomArray(n, 0, n);
    cout<<inversionCount(arr, n)<<endl<<endl;
    delete[] arr;

    // 测试2: 测试完全有序的数组
    // 结果应该为0
    cout<<"Test Inversion Count for Ordered Array, n = "<<n<<" :"<<endl;
    arr = TestHelper::generateOrderedArray(n);
    cout<<inversionCount(arr, n)<<endl<<endl;
    delete[] arr;

    // 测试3: 测试完全逆序的数组
    // 结果应改为 N*(N-1)/2
    // 1000000->499999500000
    cout<<"Test Inversion Count for Inversed Array, n = "<<n<<" :"<<endl;
    arr = TestHelper::generateInversedArray(n);
    cout<<inversionCount(arr, n)<<endl;
    delete[] arr;

    return 0;
}