// 折半查找
#include <iostream>
using namespace std;

// 折半查找
int BiSearch(int a[], int n, int k){
    int low = 0, high = n-1, mid;
    int found = 0;
    int time = 0; // 记录查找次数
    while((low <= high) && found == 0){
        mid = (low+high)/2;
        if(k > a[mid]) low = mid+1;
        else if(k == a[mid]) found = 1;
        else high = mid -1;
        ++time;
    }
    cout<<"Search for "<<time<<" times. ";
    if(found == 1) return mid;
    return -1;
}

int main(){
    // int a[] = {1,20,33,35,66,78,88};
    int a[] = {5,13,19,21,37,56,64,75,80,88,92,100,111,120,125};
    int len = sizeof(a)/sizeof(a[0]);

    int loc;

    // test1
    loc = BiSearch(a, len, 75);
    if(loc == -1) cout<<"Found nothing."<<endl;
    else cout<<"The location is "<<loc+1<<". "<<endl;

    // test2
    loc = BiSearch(a, len, 37);
    if(loc == -1) cout<<"Found nothing."<<endl;
    else cout<<"The location is "<<loc+1<<". "<<endl;
}   