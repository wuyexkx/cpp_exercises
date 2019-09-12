#ifndef __SINGLE_LIST_H
#define __SINGLE_LIST_H

template<class T>
class Node
{
public:
    Node(): link(nullptr), data(T()) { }
    T data;
    Node* link;
};


template<class T>
class List
{
public:
    List(): first(nullptr) { }
    ~List() 
    {
        while(first)
        {
            delete first;
            first = first->link;
        }
    }
private:
    Node<T>* first;
};

#endif