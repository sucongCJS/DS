// 有平行边
// 稀疏图 邻接表
#ifndef GRAPH_SPARSEGRAPH_H
#define GRAPH_SPARSEGRAPH_H

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class SparseGraph{
private:
    int n, m; // 点数, 边数
    bool directed;
    vector<vector<int>> g;
public:
    SparseGraph(int n, bool directed){
        this->n = n;
        this->m = 0;
        this->directed = directed;
        g = vector<vector<int>>(n, vector<int>());
    }

    ~SparseGraph(){}

    int V(){return n;}
    int E(){return m;}

    bool hasEdge(int v, int w){
        assert( v >= 0 && v < n);
        assert( w >= 0 && w < n);

        for(int i=0; i<g[v].size(); i++)
            if(g[v][i] == w)
                return true;
        return false;
    }

    void addEdge(int v, int w){
        assert( v >= 0 && v < n);
        assert( w >= 0 && w < n);

        // 允许平行边存在, 不然变O(n)
        // if(hasEdge(v, w))
        //     return;

        g[v].push_back(w);
        if(!directed)
            g[w].push_back(v);

        m++;
    }

    void show(){
        for(int i=0; i<n; i++){
            cout<<"vertex"<<i<<":\t";
            for(int j=0; j<g[i].size(); j++)
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    // 使用迭代器可以隐藏迭代的过程, 按照一定顺序访问一个容器里面的所有元素
    class adjIterator{ // adjoing 相邻
    private:
        SparseGraph &G; // 用引用比用指针安全, 因为引用不能为空, 且一旦赋值后不能更改(如果能够保证对指针的控制正确, 也能使用指针)
        int v;
        int index;
    public:
        adjIterator(SparseGraph &graph, int v): G(graph){ // 用构造列表的方式初始化
            this->v = v; // 显示地初始化(当然也能放在构造列表中)
            this->index = 0;
        }

        int begin(){
            index = 0; // 显式地将index归0, 从第一个开始
            if(G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        int next(){
            if(++index < G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        bool end(){
            return index >= G.g[v].size();
        }
    };
};

#endif // GRAPH_SPARSEGRAPH_H