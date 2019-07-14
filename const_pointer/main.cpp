#include <iostream>

using namespace std;


void f(const int* x);
void f(const int* x)
{
//    (*x)++; // 尝试改变x所指向的内容，报错
    cout << *x << endl;
}


int main()
{
    // warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
    // char * 背后的含义是：给我个字符串，我要修改它，而理论上，我们传给函数的字面常量是没法被修改的
    // 有警告，因为char *初衷是该变量及指向的空间都可以被修改，这里指向的空间不可被修改。
    char *a = "hello world!"; 

    // const char * 背后的含义是：给我个字符串，我只读取它
    // b所指对象不能变，没毛病。但b可变，已知*b为const
    const char *b = "HELLO WORLD!";

    // warning: ISO C++ forbids converting a string constant to 'char*' [-Wwrite-strings]
    // a在定义时已经指向了const空间。现在改变a的指向。
    // 有警告，因为char *初衷是该变量及指向的空间都可以被修改，这里指向的空间不可被修改。
    a = "changed";
    
    // // 编译不报错，运行死掉
    // //a指向的空间为const空间，在代码段里，可读不可写。
    // *a = 'a'; 
    // a[0] = 'a';

    // b所指对象不能变，但b可变
    b = a; // b指向了"hello world!"
    // // 编译不通过，因为已知*b为const
    // // error: assignment of read-only location '* b'
    // *b = 'a';

    cout << "a: " << a << endl;

    // // 没有初始化的可变指针（野指针）
    // // 虽然没问题,但如果后面也没对c赋值，却对c指向的空间进行了修改或者想读取所指内容，那将可能出大问题,
    // // 如果默认给c分配的值恰好指向核心存储区域，那系统将崩掉。
    char *c;
    // char d = *c; // 语法正确，编译通过，运行死掉
    // *c = 'x'; // 语法正确，编译通过，运行死掉
    // *c = *a; // 语法正确，编译通过，运行死掉
    c = a; // 给指针c赋值
    cout << "c: " << c << endl;

// // 必须初始化const指针，否则编译不通过
// // 既然为const指针类型，那就是e不能被赋值的，
// // 所以 如果在初始化的时候不指定值，之后本来也无法指定，那这个变量没有存在的意义。
    // char *const e;

    // 定义并初始化const指针，注意指针初值所指向的类型
    char *const e = a;
    // e = "xxxx"; // 语法错误，e为const 肯定不得行
    // *e = "xxxx"; // 语法错误，"xxxx"将首地址赋值给char型空间，当然编译都通不过
    // *e = 'x'; // 语法正确，编译通过，运行死掉。因为e的值为a，而*a为字面常量，所以*e也是字面常量，当然不能被改变。

    char buf[5];
    // 定义并初始化const指针，注意指针初值所指向的类型
    char *const f = buf; // f指向了数组buf，f获取到数组的首地址
    *f = 'x'; // 正确，为数组第一个元素赋值
    cout << "buf[0]: " << buf[0] << endl;

    // 与 const char *g 等价，都是修饰*g不可变
    char const *g;

    // “[]”的优先级要比“*”要高
    // 定义了一个指针数组。首先p1[5]为一个数组，再int *确定该数组的类型
    // 也就是说，该数组包含 5 个指向 int 类型数据的指针
    int *p1[5];
    // “()”的优先级比“[]”高
    // 定义了一个数组指针。首先(*p1)为一个指针，再int修饰的是数组的内容
    // 也就是说，p2 是一个指针，它指向一个包含 5 个 int 类型数据的数组，数组在这里并没有名字，是个匿名数组。
    int (*p2)[5];

    return 0;
}
