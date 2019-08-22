#ifndef GRAPH_READGRAPH_H
#define GRAPH_READGRAPH_H

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <sstream>

using namespace std;

template<typename Graph>
class ReadGraph{
public:
    ReadGraph(Graph &graph, const string &filename){ // 对常量的引用不能用于修改它所绑定的对象
    // 普通引用只能绑定到对象上, 不能绑定到字面值或者某个表达式的计算结果上, 但是常量引用有两个例外情况
    // 1. 初始化常量引用的时候允许使用任意表达式作为初始值
    // 2. 允许常量引用绑定一个非常量的对象, 字面值甚至一个一般表达式 (非常量引用发生改变的时候, 常量引用也会变)
        ifstream file(filename);
        string line; // 一行行读取
        int V, E;

        assert(file.is_open());

        assert(getline(file, line));
        stringstream ss(line);
        ss>>V>>E;

        assert(V == graph.V());

        for(int i=0; i<E; i++){
            assert(getline(file, line));
            stringstream ss(line);

            int a, b;
            ss>>a>>b;

            assert(a>=0 && a<V);
            assert(b>=0 && b<V);
            graph.addEdge(a, b);
        }
    }
};

#endif // GRAPH_READGRAPH_H