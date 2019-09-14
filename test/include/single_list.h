#ifndef __SINGLE_LIST_H
#define __SINGLE_LIST_H

template<class T>
class Node
{
public:
    Node(const T& dt = T())
    : link(nullptr), data(dt) { }
    T data;
    Node* link;
};


template<class T>
class List
{
public:
    List(): first(nullptr) { }
    ~List() // 为什么会出问题，不清楚
    {
        while(!isEmpty())
        {
            delete first; 
            first = first->link;       
        }
    }
    void Push_front(const T& item)
    {
        Node<T>* newNode = new Node<T>(item);
        newNode->link = first;
        first = newNode;
    }
    bool isEmpty() const { return first == nullptr; }

private:
    Node<T>* first;
};

#endif