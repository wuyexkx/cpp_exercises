#ifndef __MYSTRING__
#define __MYSTRING__

#include <iostream>
#include <cstring>
using namespace std;


// 带指针的类，一定要自己写构造、拷贝构造、拷贝赋值函数
// 默认为： a = b，为浅拷贝，只拷贝了指针。a内的指针和b内的指针指向同一个东西，一个修改东西另一个跟着改变了。
// 修改拷贝构造函数后，a = b，系统会拷贝b内的指针所指向的东西，并将其地址重新赋值给a内的指针
// String a(b); 以b为初值构造一个a。 String a = b; a为新构造出的，所以会调用构造函数。完全一样

class String
{
public:
    // big three 三巨头
    String(const char* str = 0);            // 构造函数
    String(const String& str);              // 拷贝构造函数
    String& operator = (const String& str); // 拷贝赋值函数
    ~String();                              //析构函数

    char* get_c_str() const { return m_data; } // inline。不改变数据 const。

private:
    char* m_data;
};


inline // 构造函数
String::String(const char* str)
{
    if(str) // 如果有初值
    {
        m_data = new char[strlen(str) + 1]; // 分配空间。1默认末尾考虑到"\0" 
        strcpy(m_data, str); // 深拷贝
    }
    else { // 未指定初值时，给空字符串
        m_data = new char[1];
        *m_data = '\0'; 
    }
}

inline // 拷贝构造函数
String::String(const String& str)
{
    m_data = new char[ strlen(str.m_data) + 1 ]; // 分配空间。1默认末尾考虑到"\0" 
    strcpy(m_data, str.m_data); // 深拷贝
}

inline String& // 拷贝赋值函数。 先清空原来，再分配参数一样大小的空间，最后拷贝过去
String::operator = (const String& str)
{
    if(this == &str) // 检测到拷贝自己
        return *this; // 如果没有此判断，发生拷贝自己时，先释放，m_data悬空，然后重新分配时会出错。

    delete[] m_data; // m_data不再指向原来的东西，指针悬空了
    m_data = new char[strlen(str.m_data) + 1]; // 重新分配空间
    strcpy(m_data, str.m_data); // 拷贝
    return *this;
}

inline // 析构函数
String::~String()
{
    delete[] m_data; // 释放动态分配的内存，否则内存泄漏
}

// 重载 << 符号
inline ostream&
operator << (ostream& os, const String& str)
{
    return os << str.get_c_str();
}

#endif