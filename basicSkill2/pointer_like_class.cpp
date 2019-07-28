#include <iostream>
using namespace std;

// ----------------pointer-like-class 关于智能指针------------------
// 创建的对象像指针, 类似*p p->func()

template<class T> // T是一种 类
class share_ptr
{
public:
    // 构造函数参数是类型为T指针,将此指针赋值给private T型指针px
    share_ptr(T* ptr): px(ptr) { }
    // 关于智能指针的一定有* ->的重载,写法就是下面这样
    T& operator* () const // 用法*p *传入参数为this,此对象有px,返回*px,返回接收可为引用,因为*px与此对象共存,并不会在这个作用于域}消失
    { return *px; }
    T* operator-> () const // ->左边为T型指针,所以返回px ,此px就是new Foo
    { return px; }
    // ~share_ptr() { delete px; } // 不知道new之后在哪里delete?
private:
    T* px; // 私有T型指针
    long* pn;
};
struct Foo
{
    void method() { cout << "Foo::method()" << endl; }
};


// 视频里边的方法,暂时不懂多个template参数怎么用
// // ----------------pointer-like-class 关于迭代器------------------
// // 迭代器代表容器里的一个元素,需要去指向一个元素,因此pointer-like
// // 以双向链表为例

// // 双向链表的节点结构 , T为节点的数据类型
// template<typename T>
// struct __list_node
// {
//     void* prev;
//     void* next;
//     T data;
// };
// // 双向列表迭代器
// template<class T, class Ref, class Ptr>
// struct __list_iterator
// {
//     typedef __list_iterator<T, Ref, Ptr> self;
//     typedef Ptr pointer;
//     typedef Ref reference;
//     typedef __list_node<T>* link_type; 
//     link_type node; // 定义节点的指针, (*node)为一个节点对象,包含prev next data成员

//     reference operator* () { return (*node).data; } // *p 返回该节点的数据
//     pointer operator-> () { return &(operator* ());} // 返回该节点数据的指针 
// };

// 修改如下
// ----------------pointer-like-class 关于迭代器------------------
// 迭代器代表容器里的一个元素,需要去指向一个元素,因此pointer-like
// 以双向链表为例

// 双向链表的节点结构 , T为节点的数据类型
template<typename T>
struct __list_node
{
    void* prev;
    void* next;
    T data;
};
// 双向列表迭代器
template<class T>
struct __list_iterator
{
    typedef __list_node<T>* link_type; 
    link_type node; // 定义节点的指针, (*node)为一个节点对象,包含prev next data成员

    T& operator* () { return (*node).data; } // *p 返回该节点的数据
    T* operator-> () { return &(operator* ());} // 返回该节点数据的指针 
};

int main()
{
    // -------------pointer-like-class 关于智能指针----------------
    // 创建share_ptr对象 需要指定class T,然后初始值为T型指针,不知道new之后在哪里delete?
    share_ptr<Foo> sp(new Foo); // 被构造函数初始化给private px
    sp->method();  // ->返回指针px  (new Foo)->method();


    // --------------pointer-like-class 关于迭代器-----------------
    __list_iterator<Foo> iter;
    iter->method();
    (*iter).method();

// 输出:
// Foo::method()
// Foo::method()
// Foo::method()

    return 0;
}

