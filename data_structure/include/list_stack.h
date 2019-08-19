#ifndef __LIST_STACK_H
#define __LIST_STACK_H

template<class T>
class listStack;

template<class T>
class Node
{
friend class listStack<T>;
private: // 注意构造函数放在private中的
    Node(const T& dt, Node<T>* n = 0) // 链式栈 节点的构造函数, 需要data 和 link同时赋值,  与栈顶指针top结合
    : data(dt), link(n) { }
    T data;
    Node<T>* link;
};

template<class T>
class listStack
{
public:
    listStack(): top(0) { } // 链式栈的构造函数需要对 top栈顶指针初始化,表示空
    ~listStack() { MakeEmpty(); }
    void Push(const T& item);
    T& Top() const;
    void Pop();
    bool IsEmpty() const;
    void MakeEmpty();
private:
    Node<T>* top; // 栈顶指针
};
template<class T>
bool listStack<T>::IsEmpty() const
{
    return top == 0;
}
template<class T>
void listStack<T>::Push(const T& item)
{
    // 将之前的栈顶指针top 赋值给 当前节点的 link, 然后将此节点指针 赋值给 栈顶指针top
    top = new Node<T>(item, top); // 很重要的一步, 与第12行呼应
}
template<class T>
T& listStack<T>::Top() const
{
    if(!IsEmpty()) return top->data;
    std::cerr << "list stack is empty!\n";
}
template<class T>
void listStack<T>::Pop()
{
    if(!IsEmpty()) 
    {
        delete top; // 释放掉top所指的空间,但top本身的值还在
        top = top->link; // 所以在delete top之后 还可以找到top的link

        // 视频里是这样的 https://www.bilibili.com/video/av31763085/?p=19   20:01
        // Node<T>* n = top;
        // top = top->link;
        // delete n;
    }
    else std::cerr << "list stack is empty!\n";
}
template<class T>
void listStack<T>::MakeEmpty()
{
    int i = 0;
    while(!IsEmpty())
    {
        Pop();
        std::cout << "delete times: " << ++i << std::endl;
    }
}


#endif