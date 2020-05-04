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
        // 再插入数据时可以直接对prev和next赋值
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
        iterator()
        : current(0) { }
        T& operator* () // *it   *it = x 可能通过*修改节点的data
        {
            return current->data;
        }                
        iterator& operator++ () // 返回引用
        {
            current = current->next;
            return *this;
        }
        iterator operator++ (int) // 返回临时变量
        {
            iterator old = current;            
            ++(*this); // current = current->next;
            return old;
        }       
        bool operator== (const iterator & itr)
        { return (itr.current == current); }  
        bool operator!= (const iterator & itr)
        { return !(*this == itr); } // return (&itr.current != current);          
    protected:
        const List<T>* theList;                 // ?
        Node* current;    // 随着节点滑动的节点指针
        iterator(Node* n) // 用Node构造iterator，在begin end中返回
        : current(n) { }
        iterator(const List<T>& lst, Node* n)   // ?
        : theList(&lst), current(n) { }
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
        for (iterator it=rhs.begin(); it!=rhs.end(); ++it) {
            (*this).push_back(*it);
        } 
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
    { return *begin(); }
    const T& back() const
    { return *iterator(tail->prev); }    
    // 从前后插入
    void push_front(const T& d) 
    {
        // Node* newNode = new Node(d);
        // newNode->next = head->next;
        // newNode->prev = head;
        // head->next->prev = newNode;
        // head->next = newNode;
        // ++theSize;
        insert(begin(), d);
    }    
    void push_back(const T& d)    
    {
        // Node* newNode = new Node(d);
        // newNode->next = tail;
        // newNode->prev = tail->prev;
        // tail->prev->next = newNode;
        // tail->prev = newNode;
        // ++theSize;
        insert(end(), d);
    }   
    // 删除前后
    void pop_front()   
    { erase(begin()); }
    void pop_back() 
    { erase(iterator(tail->prev)); }

    // 擦除，返回下一个
    iterator erase(const iterator& itr)
    {
        Node* p = itr.current;  // 取出itr的Node
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
    // 在itr前插入新节点, 返回新节点的itr
    iterator insert(const iterator& itr, const T& d) 
    {
        // Node* newNode = new Node(d);
        // Node* rNode = itr.current;
        // newNode->next = rNode;
        // newNode->prev = rNode->prev;
        // rNode->prev->next = newNode;
        // rNode->prev = newNode;
        // ++theSize;
        // return iterator(newNode);
        Node* rNode = itr.current;  
        Node* newNode = new Node(d, rNode->prev, rNode);
        rNode->prev = rNode->prev->next = newNode;
        ++theSize;
        return iterator(newNode);
    }
    void clear() 
    {
        while (!ismpty()) 
            pop_front();
    }
    int size() const
    { return theSize; }
    bool ismpty() const
    { return (size() == 0); }    
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
#define NUMS    (6)    

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
    
    list.show();

    for (auto it=list.begin(); it!=list.end(); ++it) { 
        if (*it % 2)
            *it = 555;
    }
    list.show();

    cout << "\n========" << endl;

// stdout:
    // 11 10 9 8 7 6 0 1 2 3 4 5 
    // 11 9 7 0 2 4
    // clear():
    // 0 1 2 3 4 5
    // 0 5
    // 1 4
    // 1 2 3 4
    // 555 2 555 4

    // ======== 

    return 0;
}