/* 数组
    缺点: 插入 删除数据很慢,要依次移动.
    优点: 二分查找很快

   链表
    缺点: 无法二分查找,没有下标
    优点: 插入删除速度很快 

   树
    结合了数组和链表的优点, 插入删除很快, 二分查找很快
    一个叉的树是链表
*/

#include <iostream>
#include <queue>
using namespace std;

template<class T>
class binaryTree;

template<class T>
class Node // 一个树的节点
{
friend class binaryTree<T>; 
public:
    Node(const T& dt) // 构造函数, 初始化数据 两个指针为空默认无子节点
    : data(dt), llink(NULL), rlink(NULL) { }
    Node<T>* llink; 
    Node<T>* rlink;
private:
    T data;
};

template<class T>
class binaryTree
{
public:
    void preOrder();  // 前序遍历 
    void inOrder();   // 中序遍历
    void postOrder(); // 后序遍历
    void levelOrder() const; // 层序遍历
    void preOrder(const Node<T>* ); // 重载一下
    void inOrder(const Node<T>* );
    void postOrder(const Node<T>* );
    void visit(const Node<T>* currentNode) const { std::cout << currentNode->data; } // 打印当前节点数据
public:
    Node<T>* root = 0; // 跟节点
};
template<class T>
void binaryTree<T>::preOrder()
{ 
    preOrder(root); 
}
template<class T>
void binaryTree<T>::inOrder()
{ 
    inOrder(root); 
}
template<class T>
void binaryTree<T>::postOrder()
{ 
    postOrder(root); 
}
template<class T> // node--left--right
void binaryTree<T>::preOrder(const Node<T>* currentNode) // 递归实现遍历
{
    if(currentNode) // 当前节点存在
    {
        visit(currentNode); // 打印当前节点数据
        std::cout << " ";
        preOrder(currentNode->llink); // 打印左节点
        preOrder(currentNode->rlink); // 打印右节点
    }
}
template<class T>
void binaryTree<T>::inOrder(const Node<T>* currentNode)
{
    if(currentNode)
    {
        inOrder(currentNode->llink);
        visit(currentNode);
        std::cout << " ";
        inOrder(currentNode->rlink);
    }
}
template<class T>
void binaryTree<T>::postOrder(const Node<T>* currentNode)
{
    if(currentNode)
    {
        postOrder(currentNode->llink);
        postOrder(currentNode->rlink);
        visit(currentNode);
        std::cout << " ";
    }
}
/*************************************
输出当前节点数据
判断它的左右子节点是否存在, 存在则 将 节点指针 存入queue
取出queue front的数据 更新 当前节点

取出跟节点,判断 有 两个子节点, 存入queue.      输出---> 1
------
[2 a]
------
取出2这个节点, 判断 有 两个子节点, 存入queue   输出---> 2
----------
[a] [3 b]
----------
取出a这个节点, 判断 无 子节点, 不存           输出---> a
------
[3 b]
------
取出3这个节点, 判断 有 两个子节点, 存入queue   输出---> 3
----------
[b] [4 c]
----------
取出b这个节点, 判断 无 子节点, 不存           输出---> b
------
[4 c]
------
取出4这个节点, 判断 无 子节点, 不存           输出---> 4
---
[c]
---
取出c这个节点, 判断 无 子节点, 不存           输出---> c
**************************************/
template<class T>
void binaryTree<T>::levelOrder() const // 层序遍历
{
    Node<T>* currentNode = root; 
    queue<Node<T>*> q; // queue数据类型为Node指针类型
    while(currentNode) // 判断当前节点存在
    {
        visit(currentNode); // 输出数据
        std::cout << " ";
        if(currentNode->llink) q.push(currentNode->llink); // 检查左节点, 存在则push到queue
        if(currentNode->rlink) q.push(currentNode->rlink); // 检查右节点, 存在则push到queue
        if(q.empty()) return; // queue无数据, 没有存入 或者 被取完  则返回
        currentNode = q.front(); // 取出指针更新当前指针
        q.pop(); // 删除队首
    }
}


int main()
{
    Node<char> a{'1'};
    Node<char> b{'2'};
    Node<char> c{'3'};
    Node<char> d{'4'};
    Node<char> aa('a');
    Node<char> bb('b');
    Node<char> cc('c');

    a.llink = &b;
    b.llink = &c;
    c.llink = &d;
    a.rlink = &aa;
    b.rlink = &bb;
    c.rlink = &cc;
    
    binaryTree<char> bt;
    bt.root = &a;

    cout << "  pre: ";
    bt.preOrder();
    cout << endl;

    cout << "   in: ";
    bt.inOrder();
    cout << endl;

    cout << " post: ";
    bt.postOrder();
    cout << endl;

    cout << "level: ";
    bt.levelOrder();
    cout << endl;

// output:
//   pre: 1 2 3 4 c b a 
//    in: 4 3 c 2 b 1 a 
//  post: 4 c 3 b 2 a 1 
// level: 1 2 a 3 b 4 c 
    return 0;
}
