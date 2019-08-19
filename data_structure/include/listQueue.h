#ifndef __LISTQUEUE_H
#define __LISTQUEUE_H

template<class T>
class listQueue;

template<class T>
class Node
{
friend listQueue<T>;
public:
    Node<T>(const T& dt, Node<T>*n = 0) // 新节点的link 都是0,  填充数据并置link为0
    : data(dt), link(n) { }
private:
    T data;
    Node<T>* link;
};

template<class T>
class listQueue
{
public:
    listQueue<T>() // 初始 queue 的front和back为0
    :front(0), back(0) { }
    ~listQueue();
    bool IsEmpty() const;
    void enqueue(const T& item);
    T& getFront() const;
    T& getBack() const;
    T dequeue();

private:
    Node<T>* front;
    Node<T>* back;
};
template<class T>
listQueue<T>::~listQueue()
{
    while(!IsEmpty()) dequeue(); // 学会用已完成的函数
}
template<class T>
bool listQueue<T>::IsEmpty() const
{
    return 0 == front;
}
template<class T>
void listQueue<T>::enqueue(const T& item) // 重点
{
    if(IsEmpty())  // 如果queue为空时, front和back都要指向这个新节点
        front = back = new Node<T>(item);
    else          // 如果queue不为空时, back->link 和 back 要一次指向这个新节点
        back = back->link = new Node<T>(item);
}
template<class T>
T& listQueue<T>::getFront() const
{
    if(!IsEmpty()) return front->data;
    std::cerr << "list queue is empty." << std::endl;
}
template<class T>
T& listQueue<T>::getBack() const
{
    if(!IsEmpty()) return back->data;
    std::cerr << "list queue is empty." << std::endl;
}
template<class T>
T listQueue<T>::dequeue()
{
    if(!IsEmpty()) // 若无此判断 在queue空时 再次dequeue段错误
    {
        T dt = getFront();
        delete front;
        front = front->link;
        return dt;
    }
    return 99999; // 如果queue空 再次dequeue 那么返回99999, 无此句将返回0
}

#endif