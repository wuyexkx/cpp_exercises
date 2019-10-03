#ifndef __LIST_STACK_H
#define __LIST_STACK_H

template<class T>
class list_stack;

template<class T>
class Node
{
    friend class list_stack<T>;
public:
    Node(const T& dt = T())
    : data(dt), link(nullptr) { }
private:
    Node<T>* link;
    T data;
};

template<class T>
class list_stack
{
public:
    list_stack()
    : top(nullptr) { }
    ~list_stack() 
    {
        while(!is_empty())
        {
            pop();
        }
    }
    void push(const T& item);
    T& Top() const;
    void pop();
    bool is_empty() const;
private:
    Node<T>* top;
};
template<class T>
void list_stack<T>::push(const T& item)
{
    Node<T>* newNode = new Node<T>(item);
    if(is_empty())
        top = newNode;
    else
    {
        newNode->link = top;
        top = newNode;
    }   
}
template<class T>
T& list_stack<T>::Top() const
{
    if(!is_empty())
        return top->data;
    std::cerr << "list stack is empty." << std::endl;
}
template <class T>
void list_stack<T>::pop()
{
    if(!is_empty())
    {    
        auto temp = top;
        top = top->link;
        delete temp;
    }
    else
        std::cout << "list stack is empty." << std::endl;
}
template<class T>
bool list_stack<T>::is_empty() const 
{
    return top == nullptr;
}

#endif