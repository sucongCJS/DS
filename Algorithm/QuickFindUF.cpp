#include <iostream>
using std::cout;
using std::cin;
using std::endl;

class QuickFindUF{
    private:
        int * id;
    public:
        QuickFindUF(int N){
            id = new int[N];
            for(int i = 0; i < N; i++){
                id[i] = i;
            }
        }
        bool Connected(int p, int q){
            return id[p] == id[q];
        }
        void Union(int p, int q){
            int pid = id[p];
            int qid = id[q];
            for(int i = 0; i < id.length; )
        }
};