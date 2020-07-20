#include <iostream>
#include <vector>

using namespace std;

// ===========================================================
// 单链表的节点
struct snode {
    snode(int v = -1) { val = v; next = nullptr; }
    int val;
    snode* next;
};
// 单链表，有空头节点
class slist {
public:
    snode* head;
    slist() { head = new snode; }
    // 头插
    void push(int val)
    {
        snode* newnode = new snode(val);
        newnode->next = head->next;
        head->next = newnode;
    }

    void reverse()
    {
        snode* cur = head->next;
        snode* prev = nullptr;
        while (cur != nullptr) {
            snode* thenext = cur->next;
            cur->next = prev;
            prev = cur;
            cur = thenext;
        }
        head->next = prev;
    }
    // 判断是否为空
    bool isempty() const 
    { return head->next == nullptr; }
    // 打印
    void print() const
    {
        snode* p = head->next;
        while (p != nullptr) {
            cout << p->val << " ";
            p = p->next;
        }
        cout << endl;
    }
};
// ===========================================================



// 双链表节点
struct node {
    unsigned int val;
    node* prev;
    node* next;
    node(unsigned int v = 0, node* p = nullptr, node* n = nullptr) {
        val = v;
        prev = p;
        next = n;
    }
};
// 双链表，有空头节点
class list {
public:
    node* head;
    node* tail;
    list() { tail = head = new node; }
    // 尾插
    void push_back(unsigned int v) 
    {
        node* newnode = new node(v);
        if (isempty()) {
            tail = head->next = newnode;
            tail->prev = head;
            return;
        }
        newnode->prev = tail;
        tail->next = newnode;
        tail = newnode;
    }
    // 擦除值为val的节点
    void erase(unsigned int v)
    {
        node* del = find(v);
        if (del != nullptr) 
            erase(del);
    }
    // 擦除节点
    void erase(node* del)
    {
        if (del != nullptr) {
            del->prev->next = del->next;
            del->next->prev = del->prev;
        }
    }
    // 查找值为val的节点指针
    node* find(unsigned int val)
    {
        node* p = head->next;
        while (p != nullptr) {
            if (p->val == val) 
                return p;
            p = p->next;
        }    
        return nullptr;    
    }
    // 是否为空
    bool isempty() const
    { return head == tail; }
    // 翻转双链表
    void reverse()
    {
        node* first = head->next;
        node* p = first;
        while (p != nullptr) {
            node* tmp = p->prev;
            p->prev = p->next;
            p->next = tmp;
            p = p->prev;
        }
        head->next = tail;
        tail->prev = head;
        tail = first;
        tail->next = nullptr;
    }
};


bool is0bit3_5(unsigned int val)
{ return !((0x7 << 3) & val); }
unsigned int clrbit3_5(unsigned int val)
{ return (~(0x7 << 3) & val); }

void print(const list& l)
{
    node* p = l.head->next;
    while (p != nullptr) {
        cout << p->val << " ";
        p = p->next;
    }
    cout << endl;    
}
void printr(const list& l)
{
    node* p = l.tail;
    while (p != l.head) {
        cout << p->val << " ";
        p = p->prev;
    }
    cout << endl;
}


int main()
{
    vector<int> vct;
    for (int i=0; i<20; ++i) {
        vct.push_back(i);
    }

    list dl;
    for (auto v : vct) {
        dl.push_back(v);
    }

    print(dl);
    dl.reverse();
    print(dl);
    dl.reverse();
    print(dl);



    slist sl;
    for (auto v : vct) {
        sl.push(v);
    }
    sl.print();
    sl.reverse();
    sl.print();
    sl.reverse();
    sl.print();

    return 0;
}