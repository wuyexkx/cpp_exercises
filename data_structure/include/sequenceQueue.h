#ifndef __SEQUENCEQUEUE_H
#define __SEQUENCEQUEUE_H

template<class T>
class seqQueue
{
public:
    seqQueue(const int queueCap = 10);
    ~seqQueue();
    bool isEmpty() const;
    void Push(const T& item);
    T& Front() const;
    T& Rear() const;
    void Pop();
private:
    T* queue;
    int front;
    int rear;
    int capacity;
};
template<class T>
seqQueue<T>::seqQueue(const int queueCap)
: capacity(queueCap)
{
    if(capacity < 1) throw "Queue capacity must > 0\n";
    queue = new T[capacity];
    front = rear = 0;
}
template<class T>
seqQueue<T>::~seqQueue()
{
    delete[] queue;
}

template<class T>
inline bool seqQueue<T>::isEmpty() const 
{
    return front == rear;
}
template<class T>
void seqQueue<T>::Push(const T& item)
{   
    // 如果已存满,扩大空间 (首尾相邻表示存满)  
    if((rear + 1) % capacity == front) // 两种存满情况都能被检测到
    {
        // 加倍
        T* newQueue = new T[2*capacity];
        int start = (front + 1) % capacity;
        if(start < 2) // no wrap // 空白在第0个或者最后一个位置
            std::copy(queue+start, queue+start+capacity-1, newQueue);
        else // wrap,分两部分拷贝  // 空白在中间
        {
            std::copy(queue+start, queue+capacity, newQueue);
            std::copy(queue, queue+rear+1, newQueue+capacity-start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete[] queue;
        queue = newQueue;        
    }
    // if(rear == capacity - 1) rear = 0;   else rear++;
    rear = (rear + 1) % capacity; // 如果到了最后一个,回到最前面. 否则++. 两种情况都能满足
    queue[rear] = item;
}
template<class T>
T& seqQueue<T>::Front() const
{
    if(isEmpty()) throw "Queue is empty! No front element!\n";
    return queue[(front + 1) % capacity]; // 如果front已经在最后,需要回到最前面
}
template<class T>
T& seqQueue<T>::Rear() const
{
    if(isEmpty()) throw "Queue is empty! No rear element!\n";
    return queue[rear];
}
template<class T>
void seqQueue<T>::Pop()
{
    if(isEmpty()) throw "Queue is empty! No front element!\n";
    front = (front + 1) % capacity;
    queue[front].~T();
}

#endif

