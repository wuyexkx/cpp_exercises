#include<iostream>
using namespace std;

template<class T> class LoopList;
template<class T> class LoopList_iter;

// 一个单向链表节点 包含了data 和 next
template<class T>
class Node
{
friend class LoopList<T>;
friend class LoopList_iter<T>;
public:    
private:
    // 将Node的构造放在private中，只允许友元 class LoopList构造
    Node(const T& item = T()) 
    :data(item), next(nullptr) { };
    T data;
    Node<T>* next;
};

// 循环链表，必须有个空节点，然后head指向它
template<class T>
class LoopList
{
friend class LoopList_iter<T>;

public:
    LoopList()  // 头空节点，head指向了这个空节点
    : head(new Node<T>) { tailNode = head->next = head; };
    ~LoopList();
    void Insert(const T& item);
    void Delete(const T& item);
    bool IsEmpty() const;
    void Show() const;
private:
    Node<T>* head;      // 指向头空节点
    Node<T>* tailNode;  // 指向尾巴，尾插时需要，头插不需要
};

// LoopList的析构函数 从第一个节点开始依次删除 最后删除空节点
template<class T>
LoopList<T>::~LoopList() 
{
    // 从第一个节点开始依次释放空间
    while (!IsEmpty()) {
        Node<T>* del = head->next;
        head->next = del->next;
        del->data.~T(); // 先调用节点数据的析构
        delete del;     // 再释放掉节点
    }
    delete head;    // 最后释放掉构造函数里的那个头结点
}

// 无论前、后插入，head的指向不能动 永远是那个空节点
template<class T>
void LoopList<T>::Insert(const T& item)
{
    Node<T>* crtNode = new Node<T>(item);

    // // 从前面插入 图片所示  h <- 4 <- 3 <- 2 <- 1
    // crtNode->next = head->next;
    // head->next = crtNode;

    // 从后面插入 需要单独的指针保存上一个节点， (h) -> [h]1 -> 2 -> 3 -> 4 
    //  那么构造函数中那个头结点可以不要，只需要一个head指针就行了
    if (IsEmpty()) { // 插入的第一个节点  
        crtNode->next = head->next;
        head->next = crtNode;
    } else {         // 插入的其他节点 
        crtNode->next = tailNode->next;
        tailNode->next = crtNode;
    }
    tailNode = crtNode;
}

// 先找到需要删除的那个节点，然后链接其前后，再delete
template<class T>
void LoopList<T>::Delete(const T& item)
{
    Node<T>* crtNode = head->next;
    Node<T>* prevNode = head; // 开始指向空节点
    // 查找
    while (crtNode != head && crtNode->data != item) { 
        prevNode = crtNode;
        crtNode = crtNode->next;
    }
    // 找到了
    if (crtNode != head) {                             
        if (crtNode == tailNode) // 如果是最后那个节点，需要更新tailNode。否则Insert找不到尾巴了
            tailNode = prevNode;
        prevNode->next = crtNode->next;
        crtNode->data.~T();
        delete crtNode;
    }
}

// 如果头结点next指向了自己，那就是空了
template<class T>
bool LoopList<T>::IsEmpty() const
{
    return (head == head->next);
}

// 从head->next开始依次显示
template<class T>
void LoopList<T>::Show() const 
{
    Node<T>* p = head->next;
    while (p != head) {
        cout << p->data;
        p = p->next;
        if (p != head)
            cout << " -> ";
    }
    cout << endl;
}

// 循环链表的迭代器
template<class T>
class LoopList_iter
{
    typedef LoopList_iter self;
public:    
    // 迭代器初始为链表head的next节点，空不空都一样
    LoopList_iter(const LoopList<T>& l)
    : llist(l), node(llist.head->next) { }
    T& operator* () 
    { 
        if (llist.IsEmpty()) {
            // 无缓冲，无重定向，内存不足紧急情况下，还能得到输出功能的支持
            // cout需要缓冲区的
            cerr << "\nabort(), loop list is empty.\n";  
            abort();
        }
        return node->data;  
    }
    self operator++ (int) // i++ 后++   
    {
        self prev(llist);
        prev.node = node;

        // 如果是最后一个了，需要跳两次next才是第一个节点
        if (!llist.IsEmpty() && node->next == llist.head) {
            node = node->next->next;
        } else {
            node = node->next;
        }
        return prev;
    }
    self& operator++ ()
    {
        if (!llist.IsEmpty() && node->next == llist.head) {
            node = node->next->next;
        } else {
            node = node->next;
        }
        return *this;
    }
private:    
    const LoopList<T>& llist; 
    Node<T>* node;
};

// ------------------- main 测试 ---------------------
int main()
{
    #define NUMS (4)
    // 构造LoopList
    LoopList<int> LList;

    // 1. 测试插入删除成员函数
    // 插入 然后打印 
    cout << "first insert   ";
    for (int i=0; i<NUMS; ++i) LList.Insert(i);  LList.Show();
    // 删除 然后打印
    cout << "delete part    ";
    for (int i=0; i<NUMS; i+=2) LList.Delete(i); LList.Show();
    // 再删除 然后打印
    cout << "delete again   ";
    for (int i=1; i<NUMS; i+=2) LList.Delete(i); LList.Show();
    // 插入 然后打印
    cout << "insert again   ";
    for (int i=0; i<2*NUMS; ++i) LList.Insert(i); LList.Show();    
    // 再删除 然后打印
    cout << "delete again   ";
    for (int i=0; i<2*NUMS; i+=2) LList.Delete(i); LList.Show();

    // 2. 测试简单的迭代器 重载的* 和 ++
    //      主要是看是否为循环链表
    cout << "iterator++     ";
    LoopList_iter<int> it(LList);
    for (int i=0; i<10; ++i) {
        cout << *it << " ";
        it++;
    }
    cout << "\n++iterator     ";
    LoopList_iter<int> it1(LList);
    for (int i=0; i<10; ++i) {
        cout << *it1 << " ";
        ++it1;
    }
    // 手动析构
    LList.~LoopList();

    cout << "\n======== over =========" << endl;

// stdout:
    // first insert   0 -> 1 -> 2 -> 3
    // delete part    1 -> 3
    // delete again
    // insert again   0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7
    // delete again   1 -> 3 -> 5 -> 7
    // iterator++     1 3 5 7 1 3 5 7 1 3
    // ++iterator     1 3 5 7 1 3 5 7 1 3
    // ======== over =========
    return 0;
}