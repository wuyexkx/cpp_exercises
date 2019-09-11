#ifndef __SEQUENCESTACK_H
#define __SEQUENCESTACK_H

#include <iostream>

// resieze array
template<class T>
void resizeArray(T*& arr,const int prevSize, const int newSize)
{
    if(newSize >= 0) 
    {
        T* newArr = new T[newSize];
        int size = std::min(prevSize, newSize);
        std::copy(arr, arr+size, newArr);
        delete[] arr;
        arr = newArr;
    }
    else std::cout << "Array new size must >= 0." << std::endl;
}

template<class T>
class seqStack
{
public:
    seqStack(const int size = 5)
    : top(-1), crtSize(size), arrStack(new T[size]) { }
    ~seqStack() { delete[] arrStack; }
    void Push(const T& it);
    T Top() const;
    void Pop();
    int getSize() const { return crtSize; }
    void print() const 
    { 
        for(int i=0; i<=top; i++) 
            std::cout << arrStack[i] << " "; 
        std::cout << std::endl; 
    }
private:
    int top;
    int crtSize;
    T* arrStack;
};
template<class T>
void seqStack<T>::Push(const T& it)
{
    if(top >= crtSize - 1) // 存满了
    {
        resizeArray(arrStack, crtSize, crtSize << 1);
        crtSize <<= 1;
    }    
    arrStack[++top] = it;
}
template<class T>
T seqStack<T>::Top() const
{
    if(top >= 0)
        return arrStack[top];
    else
    {
        std::cout << "seqStack is empty." << std::endl;
        return -1;
    }    
}
template<class T>
void seqStack<T>::Pop()
{
    if(top >= 0)
        arrStack[top--].~T(); // 也许存放的不是简单的数据，或许是个class，需要调用对应类型的析构函数
    else
        std::cout << "seq stack is empty." << std::endl;
}


#endif