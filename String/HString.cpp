#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define MAXLEN 255
typedef int ElemType;
typedef int Status;

// 串的堆式顺序存储结构
struct HString{
    char * ch;
    int length;
}

// ??串指派 拼接?
Status StrAssign(HString &T, char * chars){
    if(T.ch) delete [] T.ch;
    int len = 0;
    char * c;
    for(c=chars; *c; ++i, ++c);
    if(!i){
        T.ch = NULL;
        T.len = 0;
    }else{
        T.ch = new char[i];
        T.ch[0..i-1] = chars[0..i-1];
        T.length=i;
    }
    return OK;
}

// 用Sub返回串S的第pos个字符起长度为len的子串
Status SubString(HString &Sub, HString S, int pos, int len){
    if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1){
        return ERROR;
    }
    if(Sub.ch) delete [] Sub.ch;
    if(len == 0){
        Sub.ch = NULL;
        Sub.length = 0;
    }else{
        
    }
}