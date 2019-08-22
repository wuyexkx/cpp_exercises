#ifndef __BINART_SEARCH_H
#define __BINARY_SEARCH_H

#include <iostream>

template<class T>
class Node;
template<class T>
class BST;

enum Boolean { FALSE, TRUE };

template<class T>
class Element // 存在的意义是 可以添加更多的数据
{
public:
    Element() { }
    Element(T k) { key = k; } 
    T key;
    // 
};
template<class T>
class Node
{
    // friend class BST<T>;
public:
    Node()
    : llink(0), rlink(0) { }
    void display(const int i); // // 显示位置 和 key, 显示当前节点数据,包括左右子节点的数据,递归
// private:
    Element<T> data;
    Node<T>* llink;
    Node<T>* rlink;
};
template<class T>
class BST
{
public:
    BST(Node<T>* rt = 0)
    : root(rt) { }
    Boolean Insert(const Element<T>& ); 
    Node<T>* Search(const Element<T>& );
    Node<T>* Search(Node<T>* , const Element<T>& ); // 递归查找
    Node<T>* IterSearch(const Element<T>& );  // 迭代查找
    void InOrder() const;
    void InOrder(const Node<T>* n) const;
    void display() { if(root) root->display(1); };
private:
    Node<T>* root;
};

//------------------Ndde-------------------
template<class T> // 位置 和 key
void Node<T>::display(const int i) // // 显示当前节点数据,包括左右子节点的数据, 递归
{
    std::cout << "position: " << i << "  element: " << data.key << std::endl; // 显示当前节点数据
    if(llink) llink->display(2 * i);     // 存在左节点, 显示左节点数据  *******必须是llink-> ********
    if(rlink) rlink->display(2 * i + 1); // 存在右节点, 显示右节点数据  *******必须是rlink-> ********
}

//-----------------------------------------

//------------------BST--------------------
template<class T>
Boolean BST<T>::Insert(const Element<T>& elmt)
{
    // 1.如果是一个空树
    if(!root) 
    {
        root = new Node<T>;
        root->data.key = elmt.key;
        return TRUE;
    }

    // 2.如果树已经有节点
    // 2.1 查找应该插入的位置
    Node<T>* crtNode = root; // 每次都从root节点开始查找
    Node<T>* p =0 ;          // 暂存上一个节点指针
    while(crtNode) // 一直到最后一层  
    {
        if(crtNode->data.key == elmt.key) return FALSE; // 不能存在相同数据的节点
        p = crtNode; // 暂存父节点
        if(elmt.key < crtNode->data.key) // 左子节点
            crtNode = crtNode->llink;    // 更新当前位置
        else                             // 右子节点
            crtNode = crtNode->rlink;    // 更新当前位置
    }
    // 2.2 查找到位置p, 插入新节点
    if(elmt.key < p->data.key)  // 插入左边, *******再次判断父节点, 准备插入新节点********
    {
        p->llink = new Node<T>; // 新节点连接到 父节点的llink
        p->llink->data.key = elmt.key; // *******给 新节点赋值*******
    }
    else                        // 插入到右边
    {
        p->rlink = new Node<T>; // 新节点连接到 父节点的llink
        p->rlink->data.key = elmt.key; // *******给 新节点赋值*******
    }
}
template<class T>
Node<T>* BST<T>::Search(const Element<T>& elmt)
{
    return Search(root, elmt);
}
template<class T>
Node<T>* BST<T>::Search(Node<T>* crtNode, const Element<T>& elmt) // 递归查找
{
    if(elmt.key == crtNode->data.key) return crtNode; // 找到就返回节点指针

    if(elmt.key < crtNode->data.key) Search(crtNode->llink, elmt); // 找左边
    else Search(crtNode->rlink, elmt);                             // 找右边
}
template<class T>
Node<T>* BST<T>::IterSearch(const Element<T>& elmt)
{
    Node<T>* crtNode = root;
    while(crtNode) // 一直找到最后
    {
        if(elmt.key == crtNode->data.key) return crtNode; // 找到就返回节点指针
        if(elmt.key < crtNode->data.key) crtNode = crtNode->llink;// 找左边
        else crtNode = crtNode->rlink;                            // 找右边
    }
}
template<class T>
void BST<T>::InOrder() const
{
    InOrder(root);
}
template<class T>
void BST<T>::InOrder(const Node<T>* n) const // 中序遍历
{
    if(n)
    {
        InOrder(n->llink);
        std::cout << n->data.key << " ";
        InOrder(n->rlink);
    }
}

//-----------------------------------------

#endif