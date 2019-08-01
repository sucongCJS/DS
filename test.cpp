/*  笔记
https://www.bilibili.com/video/av36240817/?p=2
j 为模式串中不匹配的位置
F 为模式串中 j 处之前的子串(开始不匹配的串之前的串)
F_L 为 F 左端的一个子串
F_R 为 F 右端的一个子串
F_L == F_R

模式串中第 j 个位置与主串中的第 i 个位置发生不匹配时, 应从模式串中第 next[j] 个位置与主串中第 i 个位置重新开始比较

j从0开始??
next 数组手工求法
next[1] = 0; 为特殊标记, 表示应从模式串中第一个字符与主串当前不匹配字符的下一个字符开始比较
next[j] 的值为 F_L 或 F_R 串长 +1, 若 F 中有多对"F_L 和 F_R", 则取最长的那一对
*/

#include <iostream>
using namespace std;

struct Str{
    char * ch;
    int length;
}

// ??
Status init(int L){
    Str S;
    S.length = L;
    S.ch = (char*)malloc((L+1)*sizeof(char)); //多分配一个给'\0'

}

/*获取next数组(由next[j]的值求next[j+1]的值):
若next[j]值为t, 则
(1) 若P_j == P_t, 则next[j+1] = t+1 = next[j+1] + 1;
(2) 若P_j != P_t, 则循环的将t赋值为next[t], 直到t=0或者满足(1)为止, 当t=0时, next[j+1] = 1*/
void getNext(Str substr, int next[]){
    int j=1, t=0;
    next[1] = 0;
    while(j <= substr.length){
        if(t==0 || substr.ch[j] == substr.ch[t]){
            next[j+1] = t+1;
            ++t;
            ++j;
        }else{
            t = next[t];
        }
    }
}

// KMP
int KMP(Str str, Str substr, int next[]){
    int i=1, j=1;
    while((i <= str.length) && (j <= substr.length)){
        if(str.ch[i] == substr[j] || j==0){ // 如果和模式串的第一位不匹配就都后移一位
            ++i;
            ++j;
        }else{
            j=next[j];
        }
    }
    if(j>substr.length){
        return i-substr.length;
    }else{
        return 0;
    }
}

// 穷举法
int BF(Str str, Str substr){
    int i=1, j=1, k=i;
    while((i <= str.length) && (j <= substr.length)){
        if(str.ch[i] == substr[j]){
            ++i;
            ++j;
        }else{
            j=1;
            i=++k;
        }
    }
    if(j>substr.length){
        return k;
    }else{
        return 0;
    }
}



int main(){
    Str S;
    char *a = "abcaabbcabcaabdab";
    S.ch = a;
    S.length = 18;
    int next[18];
    getNext(S, next);
}