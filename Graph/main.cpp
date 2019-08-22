#include <iostream>
#include <ctime>
#include "SparseGraph.h"
#include "DenseGraph.h"
#include "ReadGraph.h"
#include "Component.h"

using namespace std;

int main(){
    // int N = 20;
    // int M = 100;

    // srand(time(NULL));

    // SparseGraph g1(N, false);
    // for(int i=0; i<M; i++){
    //     int a = rand()%N;
    //     int b = rand()%N;
    //     g1.addEdge(a, b);
    // }

    // // O(E), E为边数
    // for(int v=0; v<N; v++){
    //     cout<<v<<" : ";
    //     SparseGraph::adjIterator adj(g1, v);
    //     for(int w=adj.begin(); !adj.end(); w = adj.next())
    //         cout<<w<<" ";
    //     cout<<endl;
    // }
    // cout<<endl;

    // DenseGraph g2(N, false);
    // for(int i=0; i<M; i++){
    //     int a = rand()%N;
    //     int b = rand()%N;
    //     g2.addEdge(a, b);
    // }

    // // O(V^2)
    // for(int v=0; v<N; v++){
    //     cout<<v<<" : ";
    //     DenseGraph::adjIterator adj(g2, v);
    //     for(int w=adj.begin(); !adj.end(); w = adj.next())
    //         cout<<w<<" ";
    //     cout<<endl;
    // }
    // cout<<endl;

    string filename1 = "testG1.txt";

    DenseGraph g1(13, false);
    ReadGraph<DenseGraph> readGraph1(g1, filename1);
    Component<DenseGraph> component1(g1);
    cout<<"TestG1.txt, Component Count: "<<component1.count()<<endl;

    string filename2 = "testG2.txt";
    DenseGraph g2(7, false);
    ReadGraph<DenseGraph> readGraph2(g2, filename2);
    Component<DenseGraph> component2(g2);
    cout<<"TestG2.txt, Component Count: "<<component2.count()<<endl;

    return 0;
}