#ifndef __LIST_H
#define __LIST_H

// 前置声明
template<class T>
class List;
template<class T>
class listIterator;

template<class T>
class ListNode
{
friend class List<T>;
friend class listIterator<T>;
public:
    ListNode(const T& item) // 构造函数 初始化data
    : data(item) { };
private:
    T data;
    ListNode<T>* link;
};

template<class T>
class List
{
friend class listIterator<T>;
public:
    List(): first(0) { }; // 初始值为0 ,该节点无后续节点
    void Insert(const T& item);
    void Delete(const T& item);
    void Invert();
    void Concatenate(const List<T>& l);
    void show() const;
private:
    ListNode<T>* first;
};

template<class T>
void List<T>::Insert(const T& item) // 在列表的最前面插入新节点
{
    ListNode<T>* newNode = new ListNode<T>(item); // 由构造函数完成 初始化data
    newNode->link = first; // 将第一个节点后移, // 如果是第一次创建的那个节点,link将是0
    first = newNode;       // 插入到最前边
}

template<class T>
void List<T>::Delete(const T& item)
{
    ListNode<T>* currentNode = first;
    ListNode<T>* prevNode = 0;
    while(currentNode && currentNode->data != item) // 查找该元素,currentNode, currentNode
    { 
        prevNode = currentNode;
        currentNode = currentNode->link; 
    }
    if(currentNode) // 如果找到了需要删除的元素
    {
        if(prevNode) prevNode->link = currentNode->link; // 如果不是第一个节点, 将前一个连接到下一个
        else first = first->link; // 如果是第一个节点
        delete currentNode; // 清空当前,对应于Insert中的new
    }
}

template<class T>
void List<T>::Invert() // 反转链表  // 0->1->2->3   1->2->3->0  2->3->1->0  3->2->1->0
{
    ListNode<T>* p = first; // 指向首
    ListNode<T>* q = 0;     // 指向尾 ,首次创建的那个节点link为0
    while(p)
    {
        ListNode<T>* prevNode = q; 

        q = p;       // q为 上一节点
        p = p->link; // p指向下一个节点
        q->link = prevNode; // 为上一个节点的指针 赋值 
    }
    first = q; // 到原来最后一个节点时 让它为first
}

template<class T>
void List<T>::Concatenate(const List<T>& b)
{
    if(!first) { first = b.first; return; } // 如果第一个链表为空
    if(b.first) // 如果第一个不为空 并且 第二个链表不为空
    {
        ListNode<T>* buttom = first; 
        while(buttom->link) buttom = buttom->link; // 找到第一个链表的尾
        buttom->link = b.first; // 找到之后重新连接到 第二个链表的头
    }
}
template<class T>
void List<T>::show() const
{
    ListNode<T>* current = first;
    while(current) // 如果指向node的指针为空 那么结束
    {
        std::cout << current->data;
        if(current->link) std::cout << " -> ";
        current = current->link; // 重新赋值下一个节点的指针
    }
    std::cout << std::endl;
}

template<class T>
class listIterator // 简单的迭代器
{
public:
    listIterator(const List<T>& l) // 构造函数
    : list(l), current(l.first) { };
    bool NotNull();
    bool NextNotNull();
    T* First();
    T* Next();
private:
    const List<T>& list;
    ListNode<T>* current;
};

template<class T>
bool listIterator<T>::NotNull()
{
    if(current) return true; // 如果不为空列表,返回true
    else return false;
}
template<class T>
bool listIterator<T>::NextNotNull()
{
    if(current->link) return true; // 如果下一个节点不为空,返回true
    else return false;
}
template<class T>
T* listIterator<T>::First() // 返回首个节点数据 的地址
{
    return &list.first->data;
}
template<class T>
T* listIterator<T>::Next() // 返回下个节点数据 的地址, 并将当前节点指针 指向下一个节点
{
    if(current)
    {
        current = current->link;
        return &current->data;
    }
    return 0;
    
}


#endif
