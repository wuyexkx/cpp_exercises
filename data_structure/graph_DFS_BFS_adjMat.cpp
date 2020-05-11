#include<iostream>
#include <cstring>
#include<stack>
#include<queue>

using namespace std;

#define MAX_SIZE    (10)

template<typename T>
class Vertex
{
public:
    Vertex(const char n, const T& d=T())
    : name(n), data(d) { }
    char name;
    T data;
};

template<typename T>
class Graph
{
public:
    Graph()
    {
        theSize = 0;
        for (int i=0; i<MAX_SIZE; ++i) 
            for (int j=0; j<MAX_SIZE; ++j) 
                adjMat[i][j] = 0;
    }
    // 递归 或者 stack
    void DFS()
    {
        if (theSize == 0) return;

        bool visited[theSize];      // 记录被访问过的顶点
        memset(visited, 0, theSize);// 初始置0
        
        stack<Vertex<T>*> vStack;       // DFS栈
        int index = 0;                  // 记录没有访问过的顶点的索引
        Vertex<T>* first = vertexTable[index];
        cout << first->name << " ";     // visited
        visited[index] = true;          // 标记被访问           
        vStack.push(vertexTable[index]);// 第一个入栈
        while (!vStack.empty()) {
            auto p = vStack.top();      // 获取栈顶
            // 查找p点周围没有被访问过的点
            for (int i=0; i<theSize; ++i) {
                if (!visited[i] && adjMat[p->name - 'A'][i]) {
                    index = i;
                    break;
                } else index = -1;
            }
            // 该顶点周围的点都被访问过了
            if (index == -1) {
                vStack.pop();
            }
            // p周围还存在没被访问过的顶点，访问，入栈
            else {
                cout << vertexTable[index]->name << " ";
                visited[index] = true;  // 标记被访问           
                vStack.push(vertexTable[index]);
            }
        }
        cout << endl;
    }
    // queue 入q就标记被访问, pop只打印
    void BFS()
    {
        bool visited[theSize];
        memset(visited, 0, sizeof(visited));

        queue<Vertex<T>*> vQueue;
        vQueue.push(vertexTable[0]);        // 从第一个顶点开始
        visited[0] = true;                  // 标记

        while (!vQueue.empty()) {
            Vertex<T>* p = vQueue.front();  // 取出队头
            vQueue.pop();
            cout << p->name << " ";         // 打印
            // 周围的点都入queue, 没有被访问过且有连接关系
            for (int i=0; i<theSize; ++i) {
                if (!visited[i] && adjMat[p->name - 'A'][i]) {
                    vQueue.push(vertexTable[i]);                // 入queue
                    visited[vertexTable[i]->name - 'A'] = true; // 标记
                }
            }
        }
    }
    void add_vertex(Vertex<T>& v) { vertexTable[theSize++] = &v; }
    void add_edge(const Vertex<T>& v1, const Vertex<T>& v2) 
    {
        adjMat[v1.name - 'A'][v2.name - 'A'] = 1;   // 对称阵
        adjMat[v2.name - 'A'][v1.name - 'A'] = 1;   // 对称阵
    }
    void print_adjmat() const 
    { 
        for (int i=0; i<theSize; ++i) {
            for (int j=0; j<theSize; ++j) 
                cout << adjMat[i][j] << " ";
            cout << endl;
        }
    }
private:
    Vertex<T>* vertexTable[MAX_SIZE];
    bool adjMat[MAX_SIZE][MAX_SIZE];
    int theSize;
};


int main()
{
    Graph<string> gh;
    Vertex<string> vA('A');
    Vertex<string> vB('B');
    Vertex<string> vC('C');
    Vertex<string> vD('D');
    Vertex<string> vE('E');
    Vertex<string> vF('F');
    Vertex<string> vG('G');

    gh.add_vertex(vA);
    gh.add_vertex(vB);
    gh.add_vertex(vC);
    gh.add_vertex(vD);
    gh.add_vertex(vE);
    gh.add_vertex(vF);
    gh.add_vertex(vG);
    gh.print_adjmat(); cout << endl;

    gh.add_edge(vA, vC);
    gh.add_edge(vA, vD);
    gh.add_edge(vA, vF);
    gh.add_edge(vB, vC);
    gh.add_edge(vC, vD);
    gh.add_edge(vE, vG);
    gh.add_edge(vF, vG);
    gh.print_adjmat(); cout << endl;

    gh.DFS();
    gh.BFS();

// stdout
    // 0 0 1 1 0 1 0
    // 0 0 1 0 0 0 0
    // 1 1 0 1 0 0 0 
    // 1 0 1 0 0 0 0
    // 0 0 0 0 0 0 1
    // 1 0 0 0 0 0 1
    // DFS: A C B D F G E 
    // BFS: A C D F B G E

    return 0;
}