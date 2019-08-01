    // 哈夫曼树
    #include <iostream>
    #include <string>
    #include <string.h>
    #include <algorithm>
    using namespace std;

    #define OK 1
    #define ERROR 0
    #define MAX_SIZE 100
    typedef char TElemType;
    typedef char **HuffmanCode;

    typedef struct HTNode{
        int weight;
        int parent, lchild, rchild;
    }* HuffmanTree;

    // 找出最小的两个未被匹配的值
    void Select(HuffmanTree HT, int n, int & s1, int & s2){
        // 找到第一个parent为0的结点
        for(int i = 1; i <= n; i++){
            if(HT[i].parent == 0){
                s1 = i;
                break;
            }
        }
        // 选最小
        for(int i = s1+1; i <=n; i++){
            if(HT[i].parent == 0 && HT[i].weight < HT[s1].weight){
                s1 = i;
            }
        }
        HT[s1].parent = 1; // 把parent设为非零, 防止再次被选中

        // 再找到第一个parent为0的结点
        for(int i = 1; i <= n; i++){
            if(HT[i].parent == 0){
                s2 = i;
                break;
            }
        }
        // 选最小
        for(int i = s2+1; i <=n; i++){
            if(HT[i].parent == 0 && HT[i].weight < HT[s2].weight){
                s2 = i;
            }
        }
    }
    // 创建哈夫曼树
    void CreateHuffmanTree(HuffmanTree & HT, int n){
        if(n <= 1) return;
        int m = 2*n-1;
        HT = new HTNode[m+1]; // 0号单元不用
        // 初始化1~m单元
        for(int i = 1; i <= m; ++i){
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
        }
        // 输入前n个单元中叶子结点的权值
        for(int i = 1; i <= n; ++i){
            cin>>HT[i].weight;
        }
        // 创建哈夫曼树
        int s1, s2;
        for(int i = n+1; i <= m; ++i){
            // 在HT[1, i-1]中选两个未被选过的weight最小的两个, 索引给s1, s2
            Select(HT, i-1, s1, s2);
            HT[s1].parent = i;
            HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
        }
    }
    // 创建哈夫曼编码 HC存储编码
    void CreateHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n){
        HC = new char * [n+1]; // 分配编码表空间
        char * cd = new char[n]; // 分配 临时 存放 每个 字符编码的动态数组空间
        cd[n-1] = '\0'; // 编码结束符
        int start, c, f;
        for(int i = 1; i <= n; ++i){
            start = n-1; // 指向最后
            c = i; //
            f = HT[i].parent; // 一直指向c的双亲结点
            // 生成编码
            while(f != 0){
                --start;
                if(HT[f].lchild == c) cd[start] = '0';
                else cd[start] = '1';
                c = f;
                f = HT[f].parent;
            }
            HC[i] = new char[n-start];
            strcpy(HC[i], &cd[start]);
        }
        delete cd;
    }

    void display(){
        cout<<"**************************************************************"<<endl;
        cout<<"**** 1. Input number of Huffman argument                  ****"<<endl;
        cout<<"**** 2. Initialize Huffman arguments(26 letters and SPACE)****"<<endl;
        cout<<"**** 3. Create Huffman Tree and Code                      ****"<<endl;
        cout<<"**** 4. Print the Huffman Code                            ****"<<endl;
        cout<<"**** 5. Input code, and print letters.                    ****"<<endl;
        cout<<"**** 6. Input letters, and print code.                    ****"<<endl;
        cout<<"**** 7. Exit.                                             ****"<<endl;
        cout<<"**************************************************************"<<endl;
    }

    void encode(const string& aphb, char** HC){
        string stn;
        getline(cin, stn, '\n');
        transform(stn.begin(), stn.end(), stn.begin(), ::tolower); // to lower
        for(int i = 0; i < stn.length(); ++i){
            for(int j = 0; j < aphb.length(); ++j){
                if(stn[i] == aphb[j]){
                    cout<<HC[j+1];
                }
            }
        }
    }

    void decode(const string& aphb, char** HC){
        string code;
        cin>>code;
        int num = aphb.length();
        // 存储是否匹配的数组, 索引对应HC的索引, 匹配为1, 不匹配为0
        int match[num+1];
        for(int i = 1; i <= num; ++i){
            match[i] = 1;
        }

        int let_code_index = 0; // 字母的编码索引
        int match_num = num;
        int start_let_code_index = 0; // 字母的编码在code中开始匹配的位置
        int let_code_len = 0; // 字母编码的长度
        for(int code_index = 0; code_index < code.length(); ++code_index){
            // 在HC中匹配具体第code_index个元素
            for(int i = 1; i <= num; ++i){
                if(match[i] == 1 && HC[i][let_code_index] != code[code_index]){
                    match[i] = 0;
                    --match_num;
                }
            }
            let_code_index++;
            // 匹配到只剩一个
            if(match_num == 1){
                for(int match_index = 1; match_index <= num; match_index++){
                    if(match[match_index] == 1){
                        cout<<"match_index: "<<match_index<<endl;
                        let_code_len = sizeof(HC[match_index])-1;
                        cout<<"len: "<<let_code_len<<endl;
                        cout<<aphb[match_index-1];
                        break;
                    }
                }
                let_code_index = 0;
                match_num = num;
                code_index = start_let_code_index + let_code_len - 1;
                //cout<<"index: "<<code_index<<endl;
                start_let_code_index = code_index;
                // 把存匹配结果的数组重新置为全1
                for(int i = 1; i <= num; ++i){
                    match[i] = 1;
                }
            }
        }
    }

    int main(){
        //// TEST 1 //////////////////////////////
        // HuffmanTree HT;
        // int num = 8;
        // CreateHuffmanTree(HT, num);
        // test: 5 29 7 8 14 23 3 11
        // for(int i = 1; i <= num*2-1; ++i) { cout<<HT[i].parent<<" "; } cout<<endl;
        // for(int i = 1; i <= num*2-1; ++i) { cout<<HT[i].lchild<<" "; } cout<<endl;
        // for(int i = 1; i <= num*2-1; ++i) { cout<<HT[i].rchild<<" "; } cout<<endl;

        // char** HC;
        // CreateHuffmanCode(HT, HC, num);
        // for(int i = 1; i <= num; ++i) { cout<<HC[i]<<" "; } cout<<endl;
        //////////////////////////////////////////

        // display();
        // int cmd = -1;
        // while(cmd != 7){
        //     cout<<"Input command number: ";
        //     cin>>cmd;
        //     if(cmd == 1){
        //         int num;
        //         cout<<"Input num: ";
        //     }
        // }


        // abcdefghijklmnopqrstuvwxyz
        string aphb = "abcdefghijklmnopqrstuvwxyz ";
        // string aphb;
        // getline(cin, aphb, '\n');


        HuffmanTree HT;
        int num = aphb.length();
        // test: 64 13 22 32 103 21 15 47 57 1 5 32 20 57 63 15 1 48 51 80 23 8 18 1 16 1 168
        cout<<"Creat Huffman Tree: ";
        CreateHuffmanTree(HT, num);
        char** HC;
        CreateHuffmanCode(HT, HC, num);


        cin.get();
        // encode(aphb, HC);
        decode(aphb, HC);



        return 0;
    }
