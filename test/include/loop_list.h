#ifndef __LOOP_LIST_H
#define __LOOP_LIST_H

template<class T>
class loop_list;

template<class T>
class Node
{
    friend class loop_list<T>;
public:
    Node(const T& dt = T())
    : data(dt), link(nullptr) { }
private:
    T data;
    Node<T>* link;
};

template<class T>
class loop_list
{
public:
    loop_list()
    : first(new Node<T>())
    { first->link = first; }
    void Insert(const T& dt);
    void Delete(const T& dt);
    void Print() const;
private:
    Node<T>* first;
};

template<class T>
void loop_list<T>::Insert(const T& dt)
{
    Node<T>* newNode = new Node<T>(dt);
    // 空节点在前面，就在空节点后面插入新节点
    newNode->link = first->link;
    first->link = newNode;
}
template<class T>
void loop_list<T>::Delete(const T& dt)
{
    Node<T>* temp = first->link;
    Node<T>* prevNode = nullptr;
    while(temp != first && temp->data != dt)
    {
        prevNode = temp;
        temp = temp->link;
    }
    if(temp != first) // 找到了
    {
        prevNode->link = temp->link;
        delete temp;
    }

}
template<class T>
void loop_list<T>::Print() const
{
    auto temp = first->link;
    while(temp != first)
    {
        std::cout << temp->data;
        temp = temp->link;
        if(temp != first) std::cout << " -> ";
    }
    std::cout << std::endl;
}

#endif