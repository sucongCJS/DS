// 有向邻接矩阵图 DFS BFS Dijkstra
// 两点不可达则设权值为MaxInt, 而不是0
// DFS BFS没有经过足够测试, 慎重
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

#define OK 1;
#define ERROR 0;
#define MaxInt 32767 // +2^15 int能存的最大数
#define MVNum 100 // 最大顶点数
typedef int Status;
typedef char VertexType; // 顶点的数据类型
typedef int ArcType; // 权值类型

struct AMGraph{
    VertexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum; // 顶点数和边数
};

// 采用邻接矩阵表示法, 创建无向图G
int LocateVex(AMGraph G, VertexType u){
    for(int i=0; i<G.vexnum; ++i){
        if(u == G.vexs[i]){
            return i;
        }
    }
    return -1;
}
Status CreateUDN(AMGraph &G){
    cin>>G.vexnum>>G.arcnum; // 输入总顶点数, 总边数
    // 依次输入顶点信息
    for(int i=0; i<G.vexnum; ++i){
        cin>>G.vexs[i];
    }
    // 初始化邻接矩阵, 边的权值均为极大值
    for(int i=0; i<G.vexnum; ++i){
        for(int ii=0; ii<G.vexnum; ++ii){ // 方形矩阵
            G.arcs[i][ii] = MaxInt;
        }
    }
    ArcType w; // 权值
    VertexType v1, v2; // 一条边依附的顶点
    int i, j; // 图中边的索引值
    for(int k=0; k<G.arcnum; ++k){
        cin>>v1>>v2>>w;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j] = w;
    }
    return OK;
}

bool visited[MVNum]; // 辅助数组 存储顶点有没有被访问的状态

// 深度优先
void DFS_AM(AMGraph G, int v){
    cout<<G.vexs[v];
    visited[v] = true;
    for(int w=0; w<G.vexnum; ++w){
        if((G.arcs[v][w]!=MaxInt) && (!visited[w])){
            DFS_AM(G, w);
        }
    }
}
void DFSTraverse(AMGraph G){
    memset(visited, false, sizeof(visited));
    for(int v=0; v<G.vexnum; ++v){
        if(!visited[v]){
            DFS_AM(G, v);
        }
    }
}

// 广度优先
int NextAdjVex(AMGraph G, int u, int w){
    while(++w < G.vexnum){ // 如果w的下一个
        if(G.arcs[u][w] != MaxInt){
            return w;
        }
    }
    return -1;
}
void BFS_AM(AMGraph G, int v){
    cout<<G.vexs[v];
    visited[v] = true;
    queue<int> q;
    q.push(v);
    int ci; // 当前结点的索引值
    while(!q.empty()){
        ci = q.front(); q.pop();
        for(int w=0; w>=0; w=NextAdjVex(G, ci, w)){ // 一开始w设置为0: 因为第一个的第一个元素是他本身, 肯定是被访问过的, 执行NextAdjVex, 之后元素从第一个开始, 第一个元素也都是已经访问的了, 执行一轮后, 都会被NextAdjVex定位到有非零的点上去
            if(!visited[w]){
                cout<<G.vexs[w];
                visited[w] = true;
                q.push(w);
            }
        }
    }
}
void BFSTraverse(AMGraph G){
    memset(visited, false, sizeof(visited));
    for(int v=0; v<G.vexnum; ++v){
        if(!visited[v]){
            BFS_AM(G, v);
        }
    }
}

// Dijkstra
void ShortestPath_DIJ(AMGraph G, int v0){ //?? v0为没有出度的点
    int n=G.vexnum; // 顶点数
    int S[n]; // 以加入到路径中的点, 加入为true
    int D[n]; // v0到各个终点的的长度的权值
    int Path[n]; // 存储点的前驱的索引, 没有则为-1
    // 初始化各个顶点
    for(int v=0; v<n; ++v){
        S[v] = false; // S设置为空集
        D[v] = G.arcs[v0][v]; // 将v0到各个终点的最短路径长度初始化
        if(D[v] < MaxInt){
            Path[v] = v0; // v0和v之间有弧将v的前驱设为v0
        }else{
            Path[v] = -1; // v0和v之间没有弧, v的前驱设为-1
        }
    }
    S[v0] = true; // 将v0加入S
    D[v0] = 0; // 源点到源点的距离为0
    // 每次求得v0到某个顶点v的最短路径, 将v加到S中
    for(int i=1; i<n; ++i){
        int v; // 最短的索引??
        int min = MaxInt; // 最短的值
        for(int w=0; w<n; ++w){
            if(!S[w] && D[w]<min){
                v = w; min = D[w];
            }
        }
        S[v] = true; // 将最短的v加入到S中
        // 更新v0出发到集合V-S上所有顶点的最短路径长度
        for(int w=0; w<n; ++w){
            if(!S[w] && (D[v]+G.arcs[v][w] < D[w])){
                D[w] = D[v] + G.arcs[v][w];
                Path[w] = v; // 将w的前驱改为v
            }
        }
    }
    for(int i=0; i<n; ++i){
        cout<<G.vexs[i]<<": "<<D[i]<<" ";
    }
}

int main(){
    AMGraph G;
    CreateUDN(G);
    ShortestPath_DIJ(G, 0); // a
}