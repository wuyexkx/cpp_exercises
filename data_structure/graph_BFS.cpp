#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// 广(宽)度优先搜索算法 Breadth First Search
// 顶点周围找,找完继续找下一个顶点的周围
// 先把第一个顶点周围的 顶点放入队列, 然后依次取出顶点,继续放入周围的队列 (一层一层的搜索)
// 使用队列,,  先放入的顶点先搜索周围其他顶点, 先进先出FIFO

#define MAXVERTEX_NUMS 20
class Graph;
class Vertex
{
    friend class Graph;
public:
    Vertex(const char dt): data(dt) { }
private:
    char data;
};
class Graph
{
public:
    Graph()
    : nVertex(0), vertexTable(new Vertex*[MAXVERTEX_NUMS]) // 初始化当前顶点个数 和 存放顶点的数组
    {
        for(int i=0; i<MAXVERTEX_NUMS; i++) // 初始化顶点状态
            visitedVtable[i] = 0; 

        for(int i=0; i<MAXVERTEX_NUMS; i++) // 初始化adjacency matrix
            for(int j=0; j<MAXVERTEX_NUMS; j++)
                adjMat[i][j] = 0;
    }
    ~Graph() { delete[] vertexTable; } // vertexTable中存放的不是new出来的Vertex, 所以只需delete数组即可
    void addVertex(Vertex& v);
    void addEdge(const Vertex& v1, const Vertex& v2);
    void printVertex() const;
    void printAdjMat() const; 
    void printDFS(); // ***********重点是printDFS()****************
    void printBFS(); // ***********重点是printBFS()****************
private:
    Vertex** vertexTable;                        // 存放顶点 
    bool visitedVtable[MAXVERTEX_NUMS];          // 存放顶点是否被遍历的状态
    bool adjMat[MAXVERTEX_NUMS][MAXVERTEX_NUMS]; // adjacency matrix
    int nVertex;                                 // 当前顶点个数 
};
void Graph::addVertex(Vertex& v)
{
    vertexTable[nVertex++] = &v;
}
void Graph::addEdge(const Vertex& v1, const Vertex& v2)
{
    adjMat[v1.data-65][v2.data-65] = 1;
    adjMat[v2.data-65][v1.data-65] = 1;
}
void Graph::printVertex() const
{
    for(int i=0; i<nVertex; i++)
        cout << vertexTable[i]->data << " ";
    cout << endl;
}
void Graph::printAdjMat() const
{
    for(int i=0; i<nVertex; i++)
    {    
        for(int j=0; j<nVertex; j++)
            cout << adjMat[i][j] << " ";
        cout << endl;
    }
}
// ----------------------------DFS---------------------------------------
void Graph::printDFS()
{
    auto vnextUnvisited = [&](const Vertex* v)->int // 返回顶点在vertexTable中的位置
    {
        for(int i=0; i<nVertex; i++)                       // 搜索adjacency matrix的每一行
            if(adjMat[v->data-65][i] && !visitedVtable[i]) // 如果给定顶点,在邻接表找到1 且 没被访问过
                return i;                                  // 返回该顶点对应表中的位置
        return -1; // 如果没找到返回-1
    };

    stack<Vertex*> gStack;  // 用stack存放 遍历过的 顶点 
    int i = 0;              // 记录顶点在vertexTable中的索引
    visitedVtable[i] = true;             // 标记第一个顶点已被访问
    cout << vertexTable[i]->data << " "; // 输出
    gStack.push(vertexTable[i]);         // 压入起点
    while(!gStack.empty())
    {
        i = vnextUnvisited(gStack.top()); // 访问第下个顶点
        if(i >= 0) // 存在
        {
            visitedVtable[i] = true;             // 标记被访问
            cout << vertexTable[i]->data << " "; // 输出
            gStack.push(vertexTable[i]);         // 访问过的顶点 都要压入stack
        }
        else // 没有下个顶点了
        {
            gStack.pop();
        }
    }
    cout << endl;
    for(int j=0; j<nVertex; j++) // 状态表置零  可以多次搜索
        visitedVtable[j] = false;
}
// -----------------------------------------------------------------------

// ----------------------------BFS----------------------------------------
void Graph::printBFS()
{
    auto vnextUnvisited = [&](Vertex* v) -> int
    {
        for(int i=0; i<nVertex; i++)
        {
            if(adjMat[v->data - 65][i] && !visitedVtable[i])
                return i;
            return -1;
        }   
    };

    queue<Vertex*> gQueue;       // 用于保存顶点
    int i = 0;                   // 用于保存当前顶点的索引
    visitedVtable[i] = true;     // 标记该顶点已被遍历
    gQueue.push(vertexTable[i]); // 存入queue
    while(!gQueue.empty()) // 遍历 queue里保存的 顶点
    {
        i = gQueue.front()->data - 65;          // 从queue中取出一个顶点,获取索引号
        int j = vnextUnvisited(gQueue.front()); // 记录 当前顶点下一个连接顶点 的起始位置, 记录adjMat的一行索引, 从第一个连接顶点开始                  // 
        while(j < nVertex) // 遍历完周围没有被 遍历过的 顶点
        {
            if(adjMat[i][j] && !visitedVtable[j]) // j对应的这个周围顶点 没有被遍历过的
            {
                visitedVtable[j] = true;          // 标记该顶点已被遍历
                gQueue.push(vertexTable[j]);      // 存入queue
            }
            j++;                                  // 寻找下一个 周围的顶点
        }
        cout << gQueue.front()->data << " "; // 当前顶点周围顶点都存进queue时, 输出当前节点
        gQueue.pop();                        // 并删除这个顶点,指向下一个
    }

    cout << endl;
    for(int ii=0; ii<nVertex; ii++) // 为方便多次搜索, 需要清零 是否被搜索过的记录
        visitedVtable[ii] = false;
}
// -----------------------------------------------------------------------


int main()
{
    Vertex vA('A');    // 创建顶点
    Vertex vB('B');
    Vertex vC('C');
    Vertex vD('D');
    Vertex vE('E');

    Graph G;           // 创建图 
    G.addVertex(vA);   // 添加顶点
    G.addVertex(vB);
    G.addVertex(vC);
    G.addVertex(vD);
    G.addVertex(vE);
    G.addEdge(vA, vB); // 添加边
    G.addEdge(vA, vD);
    G.addEdge(vB, vE);
    G.addEdge(vD, vE);
    G.addEdge(vC, vE);

    G.printVertex();  // 打印顶点
    G.printAdjMat();  // 打印邻接矩阵

    cout << "=============\n";
    G.printDFS();     // 打印深度优先搜索结果 DFS
    G.printBFS();     // 打印广度优先搜索结果 BFS
// output:
    // A B C D E 
    // 0 1 0 1 0 
    // 1 0 0 0 1 
    // 0 0 0 0 1 
    // 1 0 0 0 1 
    // 0 1 1 1 0 
    // =============
    // A B E C D 
    // A B D E C 

    return 0;
}
