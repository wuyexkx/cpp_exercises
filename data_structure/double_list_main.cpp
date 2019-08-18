#include <iostream>
#include "double_list.h"
using namespace std;

template<class T>
class Node;
template<class T>
class doubleList;

template<class T>
class Node // 
{
friend class doubleList<T>;
public:
    Node(const T& item = 9999): data(item) { } // 默认给个9999好辨别
    Node<T>* Llink() const { return llink; }   // 通过成员函数获取指针
    Node<T>* Rlink() const { return rlink; }
    T& Data() { return data; } // 加const不能作为左值
private: 
    Node<T>* llink;
    Node<T>* rlink;
    T data;
};

template<class T>
class doubleList // 双向循环链表
{
public:
    doubleList() // 构造函数, 初始链表第一个节点 数据为9999. llink和rlink都指向first
    : first(new Node<T>) 
    { first->llink = first->rlink = first; }
    Node<T>* First() { return first; } // 通过成员函数获取指针
    void Insert(Node<T>*, Node<T>*);
    void Delete(Node<T>* xNode);

private:
    Node<T>* first; 
};
template<class T> // 双向链表,往后插入节点
void doubleList<T>::Insert(Node<T>*newNode, Node<T>*xNode) // 将newNode插入到xNode的右边
{
    // 以下4行代码 英吹斯汀, 1.先连接上新节点  2.再断开之前的节点重连
    newNode->llink = xNode; 
    newNode->rlink = xNode->rlink;
    xNode->rlink->llink = newNode;
    xNode->rlink = newNode;
}
template<class T>
void doubleList<T>::Delete(Node<T>* xNode) // 删除时,1.先上一节点的r 连接到 下一节点, 2.下一节点的l 连接到上一节点
{
    if(xNode == first) cerr << "Delete the head node not permitted.\n";
    else
    {
        xNode->llink->rlink = xNode->rlink; // 上一节点的r 指向下一节点
        xNode->rlink->llink = xNode->llink; // 下一节点的l 指向上一节点
        delete xNode;
    }
}


int main()
{
    Node<int>* n1 = new Node<int>(10);
    Node<int>* n2 = new Node<int>(11);
    Node<int>* n3 = new Node<int>(12);

    cout << n1->Data() << endl;
    cout << n2->Data() << endl;
    cout << n3->Data() << endl;

    cout << "----------------------\n"; // 插入第一个节点
    doubleList<int> l;
    l.Insert(n1, l.First());
    cout << l.First()->Data() << endl;
    cout << l.First()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Data() << endl;

    cout << "======================\n"; // 接着插入两个节点
    l.Insert(n2, n1);
    l.Insert(n3, n2);
    cout << l.First()->Data() << endl;
    cout << l.First()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Rlink()->Rlink()->Data() << endl;

    l.Delete(l.First()); // 尝试删除首节点
    cout << "++++++++++++++++++++++\n"; // 删除中间的一个节点
    l.Delete(n2);
    cout << l.First()->Data() << endl;
    cout << l.First()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Data() << endl;
    cout << l.First()->Rlink()->Rlink()->Rlink()->Data() << endl;

return 0;
}
