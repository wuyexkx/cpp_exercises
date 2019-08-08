#include <iostream>
using namespace std;

class List; // 前置声明

class Node  // 单向链表的一个节点,包含数据和一个link 
{
public:;
friend class List;
private:
    int data;
    Node* link; // Node指针,用于存放同类型的下一个节点 (可以通过这个指针 找到 此节点的数据和下一个节点)
};

class List // 包含三个节点的链表
{
public:
    void test(); // 创建并赋值三个节点
    void show() const;
private:
    Node* first; // Node指针,存放链表的第一个节点
};
void List::test()
{
    Node* f = new Node; // 第一个节点
    f->data = 10;       // 第一个节点的数据
    f->link = 0;        // 假设此后面没有节点了
    first = f;          // 将第一个节点 给 链表的头

    f = new Node;       // 第二个节点
    f->data = 20;       // 第二个节点的数据
    f->link = 0;        // 假设此后面没有节点了
    first->link = f;    // 将第二个节点 连接到 第一个节点, 因为第一个节点 已经交给first

    f = new Node;       // 第三个节点
    f->data = 30;       // 第三个节点的数据
    f-> link = 0;       // 假设此后面没有节点了
    first->link->link = f; // 将第三个节点 连接到 第二个节点,因为第二个节点为first->link
}
void List::show() const
{
    cout << first->data << endl;            // 查看第一个节点的数据
    cout << first->link->data << endl;      // 查看第二个节点的数据
    cout << first->link->link->data << endl;// 查看第三个节点的数据
}


int main()
{
    List L;
    L.test();
    L.show();
    // output:
    // 10
    // 20
    // 30
    return 0;
}
