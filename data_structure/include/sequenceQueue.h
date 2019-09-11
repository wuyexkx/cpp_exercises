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


/* ==============后来写的==============================
template<class T>
void resizeArray(T*& arr, const int prevSize, const int newSize)
{
    if(newSize < 0) std::cout << "new size must >= 0." << std::endl;
    else
    {    
        T* newArr = new T[newSize];
        int size = std::min(prevSize, newSize);
        std::copy(arr, arr+size, newArr);
        delete[] arr;
        arr = newArr;
    }
}

template<class T>
class seqQueue
{
public:
    seqQueue(const int cap)
    : capacity(cap), arrQueue(new T[cap]) { front = rear = 0; }
    ~seqQueue(){ delete[] arrQueue; }
    void Push(const T& it);
    bool isEmpty() const { return front == rear; }
    T& Front() const 
    { 
        if(isEmpty()) { std::cout << "sequence queue is empty.n\n"; }
        // 因为在存放第一个数据时，++rear, 所以有一个位置是空着的， 在查看front数据时需要后移一位，但是要判断front是否越界
        return arrQueue[(front + 1) % capacity];
    }
    T& Rear() const { return arrQueue[rear]; }
    void Pop();
    int Capacity() const { return capacity; }
private:
    int capacity;
    int front;
    int rear;
    T* arrQueue;
};
template<class T> 
void seqQueue<T>::Push(const T& it)
{
    if((rear + 1) % capacity == front) // full
    {
        T* arr = new T[capacity * 2];
        if(rear + 1 == capacity) // not round，直接复制，front、rear不用修改
        {
            std::copy(arrQueue, arrQueue+capacity, arr);
        }
        else // round ，分段复制, 将后半部分复制到最前面， 将前半部分依次放到后面，所以front、rear都需要改变
        {
            std::copy(arrQueue+front, arrQueue+capacity, arr); 
            std::copy(arrQueue, arrQueue+rear+1, arr+capacity-front-1);
            front = 0;
            rear = capacity - 1;
        }
        delete[] arrQueue;
        arrQueue = arr;
        capacity *= 2;
    }
    rear = (rear + 1) % capacity; // rear需要回来， 先++ 后赋值，空了一个位置
    arrQueue[rear] = it;
}
template<class T>
void seqQueue<T>::Pop()
{
    if(isEmpty())
    {
        std::cout << "sequence queue is empty." <<std::endl;
        return;
    } 
    front = (front + 1) % capacity; // 需要操作front，越界会回头
    arrQueue[front].~T();
}
*/

#endif

