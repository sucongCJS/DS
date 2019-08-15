// 路径压缩到rank为1
// 递归有消耗, 一般慢于UnionFind3.h
#ifndef UNIONFIND_UNIONFIND4_H
#define UNIONFIND_UNIONFIND4_H

#include <cassert>

using namespace std;

namespace UF4{
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
            // while(p != parent[p]){
            //     parent[p] = parent[parent[p]]; // 路径压缩
            //     p = parent[p];
            // }
            // return p;
            if(p != parent[p])
                parent[p] = find(parent[p]);
            return parent[p]; // 返回值都是相同的, 为整棵树的根结点
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