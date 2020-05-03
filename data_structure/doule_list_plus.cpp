#include<iostream>
using namespace std;
// #include<list>

// 双向非循环链表
//  包含了Node class、iterator class、List class
//  节点    包含了 data数据 prev next指针
//  迭代器  重载 *  ++  ==  != 构造函数用到了Node
//  链表    begin end 通过返回iterator获取迭代器
template<typename T>
class List 
{
// ---------------------- Node -----------------------
private:
    struct Node
    {
        T data;
        Node* prev;
        Node* next;
        Node(const T& d=T(), Node* p=0, Node* n=0)
        : data(d), prev(p), next(n) { } 
    };    
// ---------------------------------------------------

// -------------------- iterator ---------------------
public:
    class iterator // *  ++  !=  ==
    {
        friend class List;
    public:
        T& operator* () 
        {
            return current->data;
        }                
        iterator& operator++ ()
        {
            current = current->next;
            return *this;
        }
        iterator operator++ (int)
        {
            iterator old = current;            
            ++(*this); // current = current->next;
            return old;
        }       
        bool operator== (const iterator & rhs)
        { return (rhs.current == current); }  
        bool operator!= (const iterator & rhs)
        { return !(*this == rhs); } // return (&rhs.current != current);          
    protected:
        Node* current;    // 随着节点滑动的节点指针
        iterator(Node* n) // 用Node构造iterator，在begin end中返回
        : current(n) { }
    };
// ---------------------------------------------------

public:
    List() { __init(); }                // 默认构造
    List(const List& rhs)               // 拷贝构造
    { 
        *this = rhs; 
    }
    List& operator= (const List& rhs)   // 赋值构造
    {
        // 若把自己赋值给自己
        if (this == &rhs)
            return *this;

        // List对象赋值给this这个对象，先清空this对象再依次按照rhs放入
        clear();
        // for ();  ?
        return *this;
    }
    ~List()                             // 析构
    { 
        clear();    // 释放所有数据节点
        delete head;// 释放头尾节点
        delete tail;
    }
    // -------- begin and end --------
    iterator begin() const  // 通过Node构造iterator返回
    { return iterator(head->next); }
    iterator end() const
    { return iterator(tail); } 
    // -------------------------------

    // 获取链表前后数据
    const T& front() const
    {
        return *begin();
    }
    const T& back() const
    {
        return *iterator(tail->prev);
    }    
    // 从前后插入
    void push_front(const T& rhs) 
    {
        Node* newNode = new Node(rhs);
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
        ++theSize;
    }    
    void push_back(const T& rhs)    
    {
        Node* newNode = new Node(rhs);
        newNode->next = tail;
        newNode->prev = tail->prev;
        tail->prev->next = newNode;
        tail->prev = newNode;
        ++theSize;
    }   
    // 删除前后
    void pop_front()   
    {
        erase(begin());
    }
    void pop_back() 
    {
        erase(iterator(tail->prev));
    }
    // 擦除，返回下一个
    iterator erase(const iterator& it)
    {
        Node* p = it.current;   // 取出itr的Node
        iterator ret(p->next);  // 用next构造一个itr作为返回值
        p->next->prev = p->prev;// 去掉该Node的链接关系
        p->prev->next = p->next;// 
        delete p;               // 释放该Node
        --theSize;              
        return ret;
    }
    iterator erase(const iterator& start, const iterator& end)
    {
        // 加const原因 可能传入的是个临时对象，如list.begin()
        //  而引用& 不能绑定到常量或者临时对象
        for (auto it=start; it!=end; ++it) {
            erase(it);
        }
        return end;
    }    

    bool ismpty() const
    {
        return (theSize == 0);
    }
    void clear() 
    {
        while (!ismpty()) 
            pop_front();
    }
    int size() const
    { return theSize; }
    void show() const 
    {
        for (auto it=begin(); it!=end(); ++it) { 
            cout << *it << " "; 
        }  
        cout << endl;
    }
private:
    int theSize;    // list节点个数，插入 删除 empty pop用到
    Node* head;     // 头尾结点，不存数据
    Node* tail;
    void __init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;  // 非循环链表，head->prev和tail->next不用设置
        tail->prev = head;
    }
};


int main()
{
#define NUMS    (5)    

    List<int> list;
    // 存放
    for (int i=0; i<NUMS; ++i) { list.push_back(i); }
    for (int i=NUMS; i<2*NUMS; ++i) { list.push_front(i); }
    list.show();

    // 删除部分 
    int index = 0;
    for (auto it=list.begin(); it!=list.end(); ++it) {
        if (index % 2)
            list.erase(it);
        ++index;
    }
    list.show();
    
    // 清空
    cout << "clear(): ";
    list.clear();
    list.show();

    // 存放
    for (int i=0; i<NUMS; ++i) { list.push_back(i); }
    list.show();
    // 查看front  back
    cout << list.front() << " " << list.back() << endl;

    // pop掉再看
    list.pop_front();
    list.pop_back();
    cout << list.front() << " " << list.back() << endl;

    // pop掉再看
    list.pop_front();
    list.pop_back();
    cout << list.front() << " " << list.back() << endl;    

    // pop掉再看
    list.pop_front();
    list.pop_back();
    cout << list.front() << " " << list.back() << endl; 

    cout << "\n========" << endl;

// stdout:
//     9 8 7 6 5 0 1 2 3 4 
//     9 7 5 1 3
//     clear():
//     0 1 2 3 4  
//     0 4
//     1 3
//     2 2
//     Segmentation fault    

    return 0;
}