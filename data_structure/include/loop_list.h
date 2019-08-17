#ifndef __LOOP_LIST
#define __LOOP_LIST

// 前置声明
template<class T>
class loopList;
template<class T>
class loopList_Iterator;

template<class T>
class ListNode  // 链表的一个节点
{
friend class loopList<T>;
friend class loopList_Iterator<T>;
public:
    ListNode(const T item = 0) // 构造函数 初始化data
    : data(item) { };
private:
    T data; // 本节点所存储的数据
    ListNode<T>* link; // 连接到下一个节点的指针变量
};

template<class T>
class loopList // 循环链表
{
friend class loopList_Iterator<T>;
public:        // 循环链表的构造函数 , 一定要指向自己
    loopList(): first(new ListNode<T>) { first->link = first; }; // first为空节点, 指向自己,,循环链表非常重要的一步
    void Insert(const T& item);
    void Delete(const T& item);
    void show() const;
private:
    ListNode<T>* first;
};

template<class T> // 第一个节点为空,数据从第二个节点开始的
void loopList<T>::Insert(const T& item) // 在列表的第二个节点前 插入新节点
{
    // 从前面插入
    ListNode<T>* newNode = new ListNode<T>(item); // 由构造函数完成 初始化data
    newNode->link = first->link; // 将第二个节点后移, // 如果是第一次创建的那个节点,link将是0
    first->link = newNode;       // 取代第二个节点

    // // 从后面插入
    // ListNode<T>* newNode = new ListNode<T>(item);
    // static ListNode<T>* prevNode;
    // if(first->link == first) // 如果是首次插入数据,需要断开first-link ---> first
    // {
    //     newNode->link = first->link;
    //     first->link = newNode;
    // }
    // else  // 如果非首次插入, 那就在上次基础上重新link
    // {
    //     newNode->link = prevNode->link;
    //     prevNode->link = newNode;
    // }
    // prevNode = newNode; // 每次都要备份插入节点 的地址
}

template<class T>
void loopList<T>::Delete(const T& item)
{
    ListNode<T>* currentNode = first->link; // 从第二个节点开始
    ListNode<T>* prevNode = 0;
    while(currentNode != first && currentNode->data != item) // 查找该元素,currentNode, currentNode
    { // 只要没有回到第一个节点 并且 不是要找的数据,那就继续下一个节点
        prevNode = currentNode;  // 备份前一个节点,
        currentNode = currentNode->link; // 继续往下找
    }
    if(currentNode != first) // 如果找到了需要删除的元素 (不是第一个空节点, 并且 跳出循环, 说明找到了)
    { // 有了表头的空节点,判断会少一些
        prevNode->link = currentNode->link; // 空出这个节点
        delete currentNode; // 清空当前,对应于Insert中的new
    }
}
template<class T>
void loopList<T>::show() const
{
    ListNode<T>* current = first->link;
    while(current != first) // 如果指向node的指针为空 那么结束
    {
        std::cout << current->data;
        current = current->link; // 重新赋值下一个节点的指针
        if(current != first) std::cout << " -> ";
    }
    std::cout << std::endl;
}

template<class T>
class loopList_Iterator // 简单的迭代器
{
public:
    loopList_Iterator(const loopList<T>& l) // 构造函数
    : list(l), current(l.first->link) { };
    bool NotNull();
    bool NextNotNull();
    T* First();
    T* Next();
private:
    const loopList<T>& list;
    ListNode<T>* current;
};

template<class T>
bool loopList_Iterator<T>::NotNull()
{
    if(current != list.first) return true; // 如果不是指向的空节点,返回true
    else return false;
}
template<class T>
bool loopList_Iterator<T>::NextNotNull()
{
    if(current->link != list.first) return true; // 如果下一个节点不为空,返回true
    else return false;
}
template<class T>
T* loopList_Iterator<T>::First() // 返回首个节点数据 的地址
{
    if(list.first->link != list.first) return &list.first->link->data;
    else return 0; // 当列表为空时, 返回0, 使用*obj.First()出错
}
template<class T>
T* loopList_Iterator<T>::Next() // 返回下个节点数据 的地址, 并将当前节点指针 指向下一个节点
{
    current = current->link;     // 先往后挪动
    if(current == list.first)    // 再判断是否为空头节点
    {
        current = current->link; // 如果是空头节点,继续往后挪动
    }
    return &current->data;
}


#endif
