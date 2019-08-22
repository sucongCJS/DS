// 求图的连通分量的个数
#ifndef GRAPH_COMPONENT_H
#define GRAPH_COMPONENT_H

#include <iostream>
#include <cassert>

using namespace std;

template<typename Graph>
class Component{
private:
    Graph &G;
    bool* visited;
    int ccount;
    int* id; // 如果是同一个连通分量, id相同

    void dfs(int v){
        visited[v] = true;
        id[v] = ccount;
        typename Graph::adjIterator adj(G, v); // typename指出adjIterator是Graph中定义的一个类别, 如果没有关键字typename, adjIterator会被当成是一个static成员
        // !!: 如果要把一个template中的某个标识符号指定为一种类别, 就算是意图明显, 关键字typename也不能省略. 因此, C++的一般规则是除了使用typename修饰外, template内的任何表示符号都被视为一个值而不是一个类别(对象)
        for(int i=adj.begin(); !adj.end(); i=adj.next())
            if(!visited[i])
                dfs(i);
    }

public:
    Component(Graph &graph):G(graph){
        visited = new bool[G.V()];
        ccount = 0;
        id = new int[G.V()];
        for(int i=0; i<G.V(); i++){
            visited[i] = false;
            id[i] = -1;
        }

        for(int i=0; i<G.V(); i++)
            if(!visited[i]){
                dfs(i);
                ccount++;
            }
    }

    ~Component(){
        delete[] visited;
        delete[] id;
    }

    int count(){
        return ccount;
    }

    bool isConnected(int v, int w){
        assert(v>=0 && v<V);
        assert(w>=0 && w<V);
        return id[v] == id[w];
    }
};

#endif // GRAPH_COMPONENT_H