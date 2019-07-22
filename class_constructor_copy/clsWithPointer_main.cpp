#include <iostream>
#include "clsWithPointerMember.h"


int main()
{
    
    String s1;   // 调用自定义构造函数
    // 构造对象的错误写法，错误原因：声明了一个返回值为String类型的函数，函数名为s1
    // String s1(); 

    String s2("Hello");
    
    // 拷贝构造
    String s3(s1);
    cout << s3 << endl;

    // 拷贝赋值
    s3 = s2; 
    cout << s3 << endl;
 
    return 0;
}



