#ifndef UNIONFIND_UNIONFIND1_H
#define UNIONFIND_UNIONFIND1_H

#include <iostream>
#include <cassert>

using namespace std;

namespace UF1{
    class UnionFind{
    private:
        int* id;
        int count;

    public:
        UnionFind(int n){
            id = new int[n];
            count = n;
            for(int i=0; i<n; i++)
                id[i] = i;
        }

        ~UnionFind(){
            delete[] id;
        }

        int find(int n){
            assert(n >=0 && n < count);
            return id[n];
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){
            int pID = find(p);
            int qID = find(q);

            if(pID == qID)
                return;

            for(int i=0; i<count; i++)
                if(id[i] == pID)
                    id[i] == qID;
        }
    };
}

#endif