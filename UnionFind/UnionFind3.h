// 路径压缩: 直接和父亲的父亲连
// 近乎是O(1)
#ifndef UNIONFIND_UNIONFIND3_H
#define UNIONFIND_UNIONFIND3_H

#include <cassert>

using namespace std;

namespace UF3{
    class UnionFind{
    private:
        int* parent;
        int* rank; // rank[i]表示以i为根的集合所表示的树的层数
        int count;

    public:
        UnionFind(int count){
            parent = new int[count];
            rank = new int[count];
            this->count = count;
            for(int i=0; i<count; i++){
                parent[i] = i;
                rank[i] = 1;
            }
        }

        ~UnionFind(){
            delete[] parent;
            delete[] rank;
        }

        int find(int p){
            assert(p >=0 && p < count);
            while(p != parent[p]){
                parent[p] = parent[parent[p]]; // 路径压缩
                p = parent[p];
            }
            return p;
        }

        bool isConnected(int p, int q){
            return find(p) == find(q);
        }

        void unionElements(int p, int q){
            int pRoot = find(p);
            int qRoot = find(q);

            if(pRoot == qRoot)
                return;
            
            if(rank[pRoot] < rank[qRoot])
                parent[pRoot] = qRoot;
            else if(rank[pRoot] > rank[qRoot])
                parent[qRoot] = pRoot;
            else{ // rank[pRoot] == rank[qRoot]
                parent[pRoot] = qRoot;
                rank[qRoot] ++;
            }
        }
    };
}

#endif