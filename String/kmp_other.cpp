/**
 * @filename      kmp.cc
 * @Synopsis      KMP algorithm 
 * @author       XIU
 * @version      1
 * @date         2016-04-21
 */
// 此代码中所用的数组，或者是字符串都是从下标1开始

#include <iostream>
#include <string.h>

using namespace std;

/* ============================================================================*/
/**
 * @Synopsis      the next index data of the model string s_mode
 *
 * @Param         s_mode: the string
 * @Param         next  : the next array
 * @Param         len   : the length of the string
 */
/* ============================================================================*/
void get_next(string s_mode, int *next, int len){
    int i = 1;
    int j = 0;
    next[1] = 0;

    //cout << len << endl;
    while (i < len){
        if (j == 0 || s_mode[i] == s_mode[j]){
            ++i;
            ++j;
            if (i > len) break;
            next[i] = j;
            if (j > len) break;
            //下面的是修正的next算法（nextval）。
            /*
            if( s_mode[i] != s_mode[j]) 
                next[i] = j;
            else next[i] = next[j];
            */
        }
        else{
            j = next[j];
        }
    }
    for (int i = 1; i < len; i++){
        cout << next[i] << " ";
    }
    cout << endl;
}

/* ============================================================================*/
/**
 * @Synopsis      利用模式串s_mode中的next函数求s_model在主串 s_primary中第pos个字符之后的位置
 *
 * @Param         s_primary
 * @Param         s_mode
 * @Param         pos
 * @Param         next
 *
 * @Returns       
 */
/* ============================================================================*/
int Index_KMP(string s_primary, string s_mode, int pos, int *next)
{
    int i = pos;
    int j = 1;

    int len_p = s_primary.size();
    int len_m = s_mode.size();

    while (i < len_p && j < len_m)
    {

        if (j == 0 || s_primary[i] == s_mode[j])
        {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }

    if (j >= len_m)
        return i - len_m;
    else
        return 0;
}

/* ============================================================================*/
/**
 * @Synopsis      output function to check the result
 *
 * @Param         s_primary
 * @Param         s_mode
 * @Param         len
 * @Param         next
 * @Param         index
 */
/* ============================================================================*/
void output(string s_primary, string s_mode, int len, int *next, int index)
{
    cout << "s_primary = " << s_primary << endl;
    cout << "s_mode = " << s_mode << endl;

    for (int i = 1; i < len; i++)
    {
        cout << next[i] << " ";
    }

    cout << endl;

    cout << "index = " << index << endl;
}
int main()
{
    string s_primary = " acabaabaabcacaabc";
    string s_mode = " abaabcac";
    int len = s_mode.size();

    int *next = new int[len];

    get_next(s_mode, next, len);

    int tmp = Index_KMP(s_primary, s_mode, 1, next);

    output(s_primary, s_mode, len, next, tmp);

    delete[] next;
    return 0;
}