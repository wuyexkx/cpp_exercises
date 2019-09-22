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
    ~List() // windows下为什么会出问题，不清楚（问题已解决，因为delete已经释放了first的内存，但还要找first->link，必然出错)
    {
        while(!isEmpty())
        {
            auto temp = first; // delete first 如果一开始释放掉first所指的内存，之后就不存在first->link了，
            first = first->link;  
            delete temp; 
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
        auto temp =  first; // delete first 如果一开始释放掉first所指的内存，之后就不存在first->link了，
        first = first->link;
        delete temp;
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
            // delete crt 一定不能先释放，否则找不到crt所指内存
            if(crt == first) first =  crt->link;
            else prev->link = crt->link;
            delete crt;
        }
    }
    void Invert()
    {
        if(isEmpty())
        {
            std::cout << "empty!" << std::endl;
            return;
        } 
        Node<T>* p = first;
        Node<T>* q = 0;
        Node<T>* prev;
        while(p)
        {
            prev = q; 

            q = p;       // q为当前操作的节点
            p = p->link; // p指向下一个节点
            q->link = prev; // 将当前操作的节点与后面的link
        }   
        first = q;       // 最后 q指向了原来的末尾节点，赋给头结点
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