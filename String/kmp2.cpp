#include <iostream>
using std::cout;
using std::endl;

// pattern为要比较的字符串
void prefix_table(char pattern[], int prefix[], int n){
    prefix[0] = 0;
    int len = 0;
    int i = 1;
    while(i < n){
        if(pattern[i] == pattern[len]){
            

        }
    }
}

int main(){
    char pattern[] = "ABABCABAA";
    int i; // 保持字符串长度
    while(pattern[i] != '\0'){
        ++i;
    }
    int prefix[i];
    int n = i;
}