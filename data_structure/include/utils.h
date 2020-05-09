#ifndef __MYUTIL_H
#define __MYUTIL_H

#include <iostream>
#include <algorithm>
using namespace std;

// 模板需要写在头文件
template<typename T> // 第一个参数为指针,传入的是指针的引用,因为需要改变指针的值
void resizeArr(T*& a, const int prevSize, const int newSize)
{
    if(newSize < 0) throw "new size must >= 0\n";
    int size = min(prevSize, newSize);
    T* arr = new T[newSize];
    std::copy(a, a+size, arr);
    delete[] a;
    a = arr; // 指针赋值,如果delete[] arr;那么a所指向的空间也不存在了
}

void print();

#endif

