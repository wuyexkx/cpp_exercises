#ifndef __MYSTACK_H
#define __MYSTACK_H

#include "myutil.h"

template<class T>
class mystack
{
public:
    mystack(int stackCapacity = 10);
    ~mystack();
    bool isEmpty() const;     // 判断是否为空
    T& Top() const;           // 弹出栈顶
    void Push(const T& item); // 压入堆栈
    void Pop();               // 删除栈顶
private:
    T* stack;     // 用于动态创建数组
    int top;      // 记录栈顶的位置
    int capacity; // 数组大小
};

template<class T>
mystack<T>::mystack(int stackCapacity)
: capacity(stackCapacity)
{
    if(capacity < 1) throw "stack capacity must > 0\n";
    stack = new T[capacity];
    top = -1; // 初始堆栈为空
}   
template<class T>
mystack<T>::~mystack()
{
    delete[] stack;
}

template<class T> // 压入堆栈
void mystack<T>::Push(const T& item)
{
    if(top == capacity - 1) // 如果堆栈存满,那就扩大容量
    {
        resizeArr(stack, capacity, 2*capacity);
        capacity *= 2;
    }
    stack[++top] = item; // push一个T类型数据,top第一次为-1,然后从0开始所以++top
}

template<class T> // 判断是否为空
inline bool mystack<T>::isEmpty() const
{
    return top == -1;
}

template<class T> // 弹出栈顶
inline T& mystack<T>::Top() const
{
    if(isEmpty()) throw "Stack is empty!\n";
    return stack[top];
}

template<class T> // 删除栈顶
void mystack<T>::Pop()
{
    if(isEmpty()) throw "Stack is empty!\n";
    stack[top--].~T(); // 如果存放的是class, 需要调用它的析构函数. 也许存放的不是简单的数据类型
}


#endif