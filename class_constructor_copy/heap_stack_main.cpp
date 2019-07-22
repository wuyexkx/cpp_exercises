#include <iostream>
#include "clsWithPointerMember.h"

/* heap(堆) and stack(栈) and 生命期
--Stack: 是存在于某作用域(scope)的一块内存空间(memory space)。
    例如当你调用函数，函数本身即会形成一个stack用来放置它所接收的参数，以及返回地址。
    在函数体内声明的变量，其所使用的内存块都取自上诉stack。

    作用域内的对象，称为stack object or auto object, 会被自动清理


--Heap: 是指操作系统提供的一块global内存空间，程序可以动态分配从中获得若干区块。


---static local objects的生命期
   ex：
    {
        static complex c2(1, 2);
    }
    c2为static obj，其生命在作用域结束之后仍然存在，直到整个程序结束。


---global object的生命期
    作用域之外的对象为全局对象。如c2
    可以视为一种static obj，其作用域是整个程序。其生命在整个程序结束后才结束。
   ex:
    complex c2(1,3);
    int main()
    {
        ...
    }


---heap object的生命期
    p1和p2所指的都是heap obj，p1所指空间生命在delete时结束；
    p2在作用域完时结束，但p2所指heap obj仍然存在。作用域之外再也不见p2，再也无法delete p2。内存泄漏。
   ex1：                              ex2:
    {                                  {
        complex* p1 = new complex;         complex* p2 = complex;
        ...                            }
        delete p1; 
    }

 */


int main()
{
    
    return 0;
}



