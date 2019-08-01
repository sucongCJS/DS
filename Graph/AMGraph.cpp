// 无向邻接矩阵图 DFS BFS Dijkstra
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
            G.arcs[i][ii] = 0;
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
        G.arcs[j][i] = G.arcs[i][j]; // 对称的也赋值为w
    }
    return OK;
}

bool visited[MVNum]; // 辅助数组 存储顶点有没有被访问的状态

// 深度优先
void DFS_AM(AMGraph G, int v){
    cout<<G.vexs[v];
    visited[v] = true;
    for(int w=0; w<G.vexnum; ++w){
        if((G.arcs[v][w]!=0) && (!visited[w])){
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
        if(G.arcs[u][w] != 0){
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
        // ??如果不是从第一个开始深度
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

int main(){
    AMGraph G;
    CreateUDN(G);

    /* test1:第一行输入顶点数, 边数, 和几个顶点的数据域, 后面几行为弧两端的顶点和弧的权值
    6 6 a b c d e f
    a b 1
    a d 1
    a c 1
    d f 1
    b e 1
    c e 1
    */
    // test2: 7 6 a e c d b f g e b 1 b a 1 e c 1 c a 1 a d 1 c f 1
    // DFSTraverse(G);
    
    // test1: 6 5 h b c d e t h b 1 h d 1 h c 1 d t 1 b e 1
    // test2: 7 6 h e c d b t z h b 1 h d 1 h c 1 d t 1 b e 1 d z 1
    // test3: 8 6 h b c d z t e a h b 1 h c 1 h d 1 b e 1 d z 1 d t 1
    // BFSTraverse(G);
}