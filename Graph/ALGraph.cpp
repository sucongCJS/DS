// 无向图邻接表图
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;

#define OK 1;
#define ERROR 0;
#define MaxInt 32767 // +MAX
#define MVNum 100 // 最大顶点数
typedef int Status;
typedef char VertexType; // 顶点的数据类型
typedef int ArcType; // 权值类型

// 边结构
struct ArcNode{
    int adjvex; // 邻接点域 该边所指向的顶点索引值
    ArcNode * nextarc; // 链域 指向下一条边的指针
    ArcType info; // 数据域 和边相关的信息(如权值)
};

// 顶点结构
typedef struct VNode{
    VertexType data; // 数据域 顶点信息
    ArcNode * firstarc; // 链域 指向单链表的第一个结点
}AdjList[MVNum];

// 图结构
struct ALGraph{
    AdjList vertices; // 邻接表
    int vexnum, arcnum; // 顶点数和弧数
    int kind; // 图的种类
};

// 采用邻接表表示法, 创建无向图G
// 输入顶点的数据域, 返回其在头结点表中的索引值
int LocateVex(ALGraph G, VertexType u){
    for(int i=0; i < G.vexnum; ++i){
        if(u == G.vertices[i].data){
            return i;
        }
    }
    return -1;
}
Status CreateUDG(ALGraph &G){
    cin>>G.vexnum>>G.arcnum;
    // 构造头结点表
    for(int i=0; i<G.vexnum; ++i){
        cin>>G.vertices[i].data; // 输入顶点值
        G.vertices[i].firstarc = NULL; // 初始化表头结点的指针域为NULL
    }
    // 构造邻接表
    VertexType v1, v2; // 一条边依附的顶点
    int i, j;
    for(int k=0; k < G.arcnum; ++k){
        cin>>v1>>v2; // 输入线两端顶点的数据域部分
        i = LocateVex(G, v1); // 索引
        j = LocateVex(G, v2);
        // 头插法
        ArcNode * p1 = new ArcNode;
        p1->adjvex = j;
        p1->nextarc = G.vertices[i].firstarc;
        G.vertices[i].firstarc = p1;
        // 将新结点*p1插入到顶点vi的边表头部
        ArcNode * p2 = new ArcNode;
        p2->adjvex = i;
        p2->nextarc = G.vertices[j].firstarc;
        G.vertices[j].firstarc = p2;
        // 将新结点*p2插入到顶点vj的边表头部
    }
    return OK;
}

bool visited[MVNum]; // 存储顶点有没有被访问的状态

// 深度优先
void DFS_AL(ALGraph G, int v){
    cout<<G.vertices[v].data;
    visited[v] = true;
    ArcNode * p = G.vertices[v].firstarc;
    while(p != NULL){
        int w = p->adjvex;
        if(!visited[w]){
            DFS_AL(G, w);
        }
        p = p->nextarc;
    }
}
void DFSTraverse(ALGraph G){
    memset(visited, false, sizeof(visited));
    for(int w=0; w<G.vexnum; ++w){
        if(!visited[w]){
            DFS_AL(G, w);
        }
    }
}

// 广度优先
void BFS_AL(ALGraph G, int v){
    cout<<G.vertices[v].data;
    visited[v] = true;
    queue<int> q;
    q.push(v);
    int cvi; // 当前顶点的索引
    int cvvi; // 当前顶点连接到的顶点的索引
    while(!q.empty()){
        cvi = q.front(); q.pop(); // 返回一个队头元素后将之出队
        ArcNode * p;
        for(p=G.vertices[cvi].firstarc; p!=NULL; p=p->nextarc){ // 如果是一个独立点, 不会执行, 且前面已经打印了, 所以一切正常
            cvvi = p->adjvex;
            if(!visited[cvvi]){
                cout<<G.vertices[cvvi].data;
                visited[cvvi] = true;
                q.push(cvvi);
            }
        }
    }
}
void BFSTraverse(ALGraph G){
    memset(visited, false, sizeof(visited));
    for(int v=0; v<G.vexnum; ++v){
        if(!visited[v]){
            BFS_AL(G, v);
        }
    }
}

int main(){
    ALGraph G;
    CreateUDG(G);

    /* DFS_test1: 第一行输入顶点数, 边数, 和几个顶点的数据域, 后面几行为弧两端的顶点
    6 6 a b c d e f 
    a b
    a d
    a c
    d f
    b e
    c e
    */
    /* DFS_test2:
    7 6 a e c d b f g
    e b
    b a
    e c
    c a
    a d
    c f
    */
    // DFSTraverse(G);

    // test1: 6 5 h b c d e t h b h d h c d t b e
    // test2: 7 6 h e c d b t z h b h d h c d t b e d z
    // test3: 8 6 a h e c d b t z h b h d h c d t b e d z
    BFSTraverse(G);
    cout<<endl;
    ALGraph G2;
    CreateUDG(G2);
    BFSTraverse(G2);
    cout<<endl;
    ALGraph G3;
    CreateUDG(G3);
    BFSTraverse(G3);
}