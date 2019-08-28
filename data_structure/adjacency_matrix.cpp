#include <iostream>
using namespace std;

// 用邻接矩阵表示图, 顶点 边
// 邻接矩阵为对称阵(两个定点相互是相连的), 对角元素为0(顶点与自己的边用0表示) 
// 简单,但是有一半的空间浪费,并且稀疏0很多.

# define MAXVERTEX_NUMS 20

// 顶点的类型,可以不用这么绕弯子,也没啥用
class Vertex
{
public:
    Vertex(const int& dt): data(dt) { }
private:
    char data;
};
// 图的类型
class Graph
{
public:
    Graph(): nVertex(0) // 都初始化0
    { 
        for(int i=0; i<MAXVERTEX_NUMS; i++)
            for(int j=0; j<MAXVERTEX_NUMS; j++)
                adjMat[i][j] = 0;
    }
    void addVertex(const char& v);                 // 主要是 使nVertex++
    void addEdge(const char& st, const char& end); // 添加顶点之间的关系
    void print() const;
private:
    Vertex* vertexTable[MAXVERTEX_NUMS]; // 可以不用这么麻烦
    bool adjMat[MAXVERTEX_NUMS][MAXVERTEX_NUMS]; // 邻接矩阵
    int nVertex;                                 // 记录顶点个数
};

void Graph::addVertex(const char& v)
{
    vertexTable[nVertex] = new Vertex(v);
    nVertex++;
}
void Graph::addEdge(const char& st, const char& end)
{
    adjMat[st-65][end-65] = 1; // 对称阵
    adjMat[end-65][st-65] = 1;
}
void Graph::print() const
{
    for(int i=0; i<nVertex; i++)
    {
        for(int j=0; j<nVertex; j++)
            std::cout << adjMat[i][j] << " ";
        std::cout << endl;
    }    
}


int main()
{
    Graph G;
    G.addVertex('A');
    G.addVertex('B');
    G.addVertex('C');
    G.addVertex('D');
    G.addVertex('E');
    G.addEdge('A', 'B');
    G.addEdge('A', 'D');
    G.addEdge('B', 'E');
    G.addEdge('D', 'E');
    G.addEdge('C', 'E');

    G.print();
// output:
    // 0 1 0 1 0 
    // 1 0 0 0 1 
    // 0 0 0 0 1 
    // 1 0 0 0 1 
    // 0 1 1 1 0

    return 0;
}