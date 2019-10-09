#ifndef __DOUBLE_LIST_H
#define __DOUBLE_LIST_H

template<class T>
class double_list;

template<class T>
class Node
{
    friend class double_list<T>;
public:
    Node(const T& dt = T())
    : data(dt), prev(nullptr), next(nullptr) { }
private:
    T data;
    Node<T>* prev;
    Node<T>* next;
};

template<class T>
class double_list  // 双向循环链表
{
public:
    double_list() 
    { 
        back = head = new Node<T>(); 
        head->next = head->prev = head;
        back->next = back->prev = back;
    }
    void push_front(const T& dt);   // 从前面添加
    void Delete(const T& dt);       // 
    void print() const;             // 正向打印
    void R_print() const;           // 反向打印
private:
    Node<T>* head;
    Node<T>* back;
};
template<class T>
void double_list<T>::push_front(const T& dt)
{
    Node<T>* newNode = new Node<T>(dt);
    if(head == back) // 首次添加节点，保存到back
        back = newNode;
    newNode->next = head->next;  // 新节点的next 连接到 右边的节点 
    newNode->prev = head;        // 新节点的prev 连接到 head
    head->next->prev = newNode;  // 右节点的prev 连接到 新节点
    head->next = newNode;        // head的 next  连接到 新节点 
}
template<class T>
void double_list<T>::Delete(const T& dt)
{
    Node<T>* temp = head->next;
    while(temp != head && temp->data != dt)
    {
        temp = temp->next;
    }
    if(temp != head) // 找到了
    {
        temp->prev->next = temp->next;  // 双向链表不需要记录前面的节点
        temp->next->prev = temp->prev;
        delete temp;
    }
    else std::cout << "No such element: " << dt <<  std::endl;
}
template<class T>
void double_list<T>::print() const
{
    Node<T>* temp = head->next;
    while(temp != head) // back->next == nullptr
    {
        std::cout << temp->data;
        temp = temp->next;
        if(temp != head) std::cout << " -> ";
    }
    std::cout << std::endl;
}
template<class T>
void double_list<T>::R_print() const
{
    Node<T>* temp = back;
    while(temp != head) 
    {
        std::cout << temp->data;
        temp = temp->prev;
        if(temp != head) std::cout << " -> ";
    }
    std::cout << std::endl;
}

#endif