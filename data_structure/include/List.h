#ifndef __LIST_H
#define __LIST_H


template<class T>
class List;

template<class T>
class ListNode
{
friend class List<T>;
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
void List<T>::Invert() // 反转链表
{
    ListNode<T>* p = first; // 指向首
    ListNode<T>* q = 0;     // 指向尾 ,首次创建的那个节点link为0
    while(p)
    {
        ListNode<T>* r = q;
        q = p; 
        p = p->link;
        q->link = r;
    }
    first = q;
}

template<class T>
void List<T>::Concatenate(const List<T>& b)
{
    if(!first) { first = b.first; return; } // 如果第一个链表为空
    if(b.first) // 如果第一个不为空 并且 第二个链表不为空
    {
        ListNode<T>* buttom = first; 
        while(buttom) buttom = buttom->link; // 找到第一个链表的尾
        buttom = b.first;
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


#endif