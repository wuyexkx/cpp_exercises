#ifndef __SEQUENCEQUEUE_H
#define __SEQUENCEQUEUE_H

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


#endif
