#include <iostream>
#include <list>
using namespace std;

template<typename T>
class Graph;

// 顶点只负责存储数据
// 每个顶点 连接的其他顶点用链表表示
// 在实现邻接表 的时候可以把 表(数组实现)和连接关系(链表实现)分开
template<typename T>
class Vertex
{
    friend class Graph<T>;
public:
    Vertex(const T& dt)
    : data(dt) { }
    T get_data() const { return data; } 
private:
    T data;
};
// 重载<<，输出Vertex数据时用到
template<typename T>
inline ostream& operator<< (ostream& os, const Vertex<T>& v)
{ return os << v.get_data(); }

template<typename T>
class Graph
{
public:
    Graph(const int n)
    : vmaxNums(n), nVertex(0), 
    vertexTable(new Vertex<T>* [vmaxNums]), // 初始话指针
    lists (new list<Vertex<T>> [vmaxNums]) { }
    void addVertex(Vertex<T>& v);
    void addEdge(const Vertex<T>& v1, const Vertex<T>& v2);
    void printVertex() const;
    void printAdjList() const;
    ~Graph() 
    {
        delete[] vertexTable; // 释放两个数组
        delete[] lists;
    }
private:
    Vertex<T>** vertexTable; // 保存顶点的指针 Vertex<T>* verTable[nums];
    list<Vertex<T>>* lists;  // lists 用来保存链表, 每个链表为 一个顶点 的连接关系  list<Vertex<T>> lists[];
    int vmaxNums;   // 最大顶点总数
    int nVertex;    // 当前顶点数量
};
template<typename T>
void Graph<T>::addVertex( Vertex<T>& v) // 添加顶点
{
    vertexTable[nVertex++] = &v; // 在数组里添加顶点, 数量++
}
template<typename T>
void Graph<T>::addEdge(const Vertex<T>& v1, const Vertex<T>& v2) // 添加边 对应关系
{
    lists[v1.get_data() - 'A'].push_back(v2); // 直接在对应的list里添加节点
}
template<typename T>
void Graph<T>::printVertex() const // 打印顶点
{
    for(int i=0; i<nVertex; i++)   // 遍历顶点数组 
        cout << vertexTable[i]->data << " "; // 输出每个顶点的数据
    cout << endl;
}
template<typename T>
void Graph<T>::printAdjList() const // 打印顶点连接关系
{
    for(int i=0; i<nVertex; i++)    // 遍历每个顶点 
    {
        cout << vertexTable[i]->get_data(); // 依次输出顶点
        for(auto l : lists[i])        // 遍历每个顶点的连接关系
            cout  << "->" << l; // Vertex<int> 重载了 <<
        cout << endl;
    }
}
int main()
{
    Vertex<char> vA('A'); // 创建5个顶点
    Vertex<char> vB('B');
    Vertex<char> vC('C');
    Vertex<char> vD('D');
    Vertex<char> vE('E');

    Graph<char> G(5); // 创建一个最大顶点数量为5的graph 
    G.addVertex(vA);  // 添加5个顶点
    G.addVertex(vB);
    G.addVertex(vC);
    G.addVertex(vD);
    G.addVertex(vE);

    G.addEdge(vA, vB); // 添加边
    G.addEdge(vA, vD);
    G.addEdge(vB, vA);
    G.addEdge(vB, vE);
    G.addEdge(vC, vE);
    G.addEdge(vD, vA);
    G.addEdge(vD, vE);
    G.addEdge(vE, vD);
    G.addEdge(vE, vC);

    G.printVertex();
    G.printAdjList();

// output:
    // A B C D E 
    // A->B->D
    // B->A->E
    // C->E
    // D->A->E
    // E->D->C

    return 0;
}