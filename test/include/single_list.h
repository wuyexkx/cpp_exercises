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
    ~List() // windows下为什么会出问题，不清楚
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
    T Front() const
    {
        if(isEmpty()) 
        {
            std::cout << "empty" << std::endl;
            return -1;
        }
        return first->data;
    }
    void Pop_front()
    {
        if(isEmpty()) 
        {
            std::cout << "empty!" << std::endl;
            return;
        }
        delete first;
        first = first->link;
    }
    void Delete(const T& item)
    {
        if(isEmpty())
        {
            std::cout << "empty!" << std::endl;
            return;
        } 
        Node<T>* crt = first;
        Node<T>* prev;
        while(crt && crt->data != item)
        {
            prev = crt;
            crt = crt->link;
        } 
        if(crt) // 找到了
        {
            delete crt;
            if(crt == first) first =  crt->link;
            else prev->link = crt->link;
        }
    }
    void Invert()
    {
        auto p = first;
        Node<T>* q = nullptr;
        while(p)
        {
            q->link = p;
            p = p->link;
        }
    }
    void print() const
    {
        if(isEmpty())
        {
            std::cout << "empty!" << std::endl;
            return;
        } 
        auto p = first;
        while(p)
        {
            std::cout << p->data;
            if(p->link) std::cout << "->";
            p = p->link;
        }
        std::cout << std::endl;
    }
    bool isEmpty() const { return first == nullptr; }

private:
    Node<T>* first;
};

#endif