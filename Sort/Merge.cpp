// 归并排序 升序
// https://www.bilibili.com/video/av9982752
#include <iostream>
using namespace std;

// 合并
// 一个数组左右两边都是有顺序的, 将其合并成一整个有顺序的数组
// input: L左边数组开始的索引, M为左右两边分隔的,M为右边数组第一个的索引, R为数组的最后一个的索引)
void Merge(int arr[], int L, int M, int R){
    int LEFT_SIZE = M-L;
    int RIGHT_SIZE = R-M+1;
    int left[LEFT_SIZE];
    int right[RIGHT_SIZE];

    // 将左边的数组填到left
    for(int i=L; i<M; ++i){
        left[i-L] = arr[i];
    }
    // 将右边的数组填到right
    for(int i=M; i<=R; ++i){
        right[i-M] = arr[i];
    }

    // 合并到原来的数组
    int l=0; // 指向left
    int r=0; // 指向right
    int o=L; // 指向原来总的original数组
    while((l < LEFT_SIZE) && (r < RIGHT_SIZE)){
        if(left[l] < right[r]){
            arr[o++] = left[l++];
        }else{
            arr[o++] = right[r++];
        }
    }
    // 如果r已经归并完了, 而l没有, 直接把剩下的并到原来的数组里
    while(l<LEFT_SIZE){
        arr[o++] = left[l++];
    }
    // 如果l已经归并完了, 而r没有, 直接把剩下的并到原来的数组里
    while(r<RIGHT_SIZE){
        arr[o++] = right[r++];
    }
}
// 分治
void MergeSort(int arr[], int L, int R){
    if(L==R){
        return;
    }
    int M = (L+R)/2; // 只能将M划为左边数组最后一个的索引, 其他划法都会陷入死循环
    MergeSort(arr, L, M);
    MergeSort(arr, M+1, R);
    Merge(arr, L, M+1, R); // Merge函数中是将M划为右边数组的第一个, 这个要调好
}

int main(){
    int arr[] = {2,8,9,10,4,5,6,7};
    // int arr[] = {6,8,10,9,4,5,2,7};
    int L = 0;
    int R = 7;

    MergeSort(arr, L, R);

    for(int i=0; i<=R; ++i){
        cout<<arr[i]<<" ";
    }
}