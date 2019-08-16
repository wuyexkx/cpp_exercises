#ifndef __LIST_TEST
#define __LIST_TEST

template<class T>
class List;

template<class T>
class listNode
{
friend class List<T>;
public:
    listNode<T>(const T& data) // 构造函数
    : data(data) { };
private:
    T data;
    listNode<T>* link;
};

template<class T>
class List
{
public:
    List<T>(): first(0) { };
    void Insert(const T& item);
    void Invert();
    void showList() const;
private:
    listNode<T>* first;
};
template<class T>
void List<T>::Insert(const T& item) // 从前面插入
{
    listNode<T>* newNode = new listNode<T>(item);
    newNode->link = first;
    first = newNode;
}
template<class T>
void List<T>::Invert()
{
    listNode<T>* p = first;
    listNode<T>* q = 0;
    while(p)
    {
        listNode<T>* prevNode = q;
        q = p;
        p = p->link;
        q->link = prevNode;
    }
    first = q;
}

template<class T>
void List<T>::showList() const 
{
    listNode<T>* currentNode = first;
    while(currentNode)
    {
        std::cout << currentNode->data;
        currentNode = currentNode->link;
        if(currentNode) std::cout << " -> ";
    }
    std::cout << std::endl;
}

#endif