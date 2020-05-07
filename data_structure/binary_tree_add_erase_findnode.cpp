#include<iostream>

using namespace std;


// 链式队列，在二叉树的层序遍历中用
// 用head和tail指针分别指向队首和尾
// -------------------- list_queue ------------------------
template<typename T>
class list_queue
{
public:
    list_queue() { head = tail = nullptr; theSize = 0; }
    ~list_queue() { while (!empty()) pop(); }
    void push(const T& item);
    T front() const;
    T back() const;
    void pop();
    bool empty() const;
    unsigned long size() const;
    void show() const;

private:
    struct Node
    {
        Node(const T& d)
        :data(d), next(nullptr) { }
        Node* next;
        T data;
    };
    Node* head;
    Node* tail;
    unsigned long theSize;
};

template<typename T>
void list_queue<T>::push(const T& item)
{
    Node* newNode = new Node(item);
    if (empty())
        head = tail = newNode;
    else
        tail = tail->next = newNode;
    ++theSize;
}

template<typename T>
T list_queue<T>::front() const 
{ 
    if (!empty()) return head->data; 
    std::cerr << "list queue is empty." << std::endl;
    exit(1); // 返回错误码，0表示正常退出  
}
template<typename T>
T list_queue<T>::back() const 
{ 
    if (!empty()) return tail->data; 
    std::cerr << "list queue is empty." << std::endl;
    exit(1); // 返回错误码，0表示正常退出       
}

template<typename T>
void list_queue<T>::pop()
{
    if (!empty()) {
        Node* p = head->next;
        delete head;
        head = p;
        --theSize;
    }
}

template<typename T>
bool list_queue<T>::empty() const
{ return (theSize == 0); }
template<typename T>
unsigned long list_queue<T>::size() const
{ return theSize; }

template<typename T>
void list_queue<T>::show() const 
{
    if (empty()) {
        std::cerr << "\nlist queue is empty." << std::endl;
        exit(1); // 返回错误码，0表示正常退出             
    }
    Node* p = head;
    while (p) {
        cout << p->data;
        if (p != tail)
            cout << " -> ";
        p = p->next;
    }
    cout << endl;
}
// --------------------------------------------------------



// 树的节点保存的数据用Element表示，其中包括了key和val
//  讲道理key应该由hash得到
// ------------ Element ---------------
template<typename T> 
class Element
{
public:    
    Element(unsigned long k, const T& v=T()) 
    :key(k), val(v) { }
    unsigned long key;
    T val;
};
// ------------------------------------
// ------------- BtNode ---------------
template<typename T> 
class BtNode
{
public:
    // friend class BinTree;
    BtNode(const Element<T>& d, BtNode* l=nullptr, BtNode* r=nullptr)
    : data(d), llink(l), rlink(r) { }
    // 用中序遍历的方法显示节点位置和数据，递归 左子节点序号2*i 右2*i+1
    void display(unsigned long i) const
    {   
        if (llink) llink->display(2 * i);
        cout << "position: " << i << " - key: " << data.key << " - val: " << data.val << endl;
        if (rlink) rlink->display(2 * i + 1);
    }

    Element<T> data;
    BtNode<T>* llink;
    BtNode<T>* rlink;
};
// ------------------------------------

// ---------------- BinTree ---------------------
template<typename T>
class BinTree
{
private:
    BtNode<T>* root;
    unsigned long theSize;

public:
    BinTree(BtNode<T>* r=nullptr)
    : root(r), theSize(0) { }
    ~BinTree() { }
    bool insert(const Element<T>& elmt);    // 容易实现
    bool erase(const Element<T>& elmt);     // 分三种情况
    BtNode<T>* findnode(const Element<T>& elmt, int* dir);
    void inorder() const;
    void inorder(BtNode<T>* n) const;
    void levelorder() const; 
    void levelorder(BtNode<T>* n) const;
    void display() const;
    unsigned long size() const;
};
// 将元素插入到树
//  1.找到合适的位置
//  2.连接节点
template<typename T>
bool BinTree<T>::insert(const Element<T>& elmt)
{
    if (!root) {
        root = new BtNode<T>(elmt);
        ++theSize;
        return true;
    }
    // 首先查找合适的位置
    BtNode<T>* p = root;
    BtNode<T>* prev;
    while (p) {
        if (elmt.key == p->data.key) 
            return false;
        prev = p;
        if (elmt.key > p->data.key) 
            p = p->rlink;
        else 
            p = p->llink;
    }
    // 找到了合适的位置
    if (elmt.key > prev->data.key)
        prev->rlink = new BtNode<T>(elmt);
    else
        prev->llink = new BtNode<T>(elmt);
    ++theSize;

    return true;   
}
// 由于二叉查找树的性质，
// 如果将当前节点替换为左子树中最大的 或 右子树中最小的一定不会破坏二叉查找树的结构
// 参考：https://blog.csdn.net/zxnsirius/article/details/52131433，链接代码有误
// 三种情况：
//  1.无左子树，也处理无子树的情况。内部判断是否为根节点的情况
//  2.无右子树，                  内部判断是否为根节点的情况
//  3.有左右子树，找到左子树最大节点，将此节点data拷贝到这里。最大结点就是左第一个，最大结点不是左第一个
template<typename T>
bool BinTree<T>::erase(const Element<T>& elmt)
{
    // 查找到需要删除的节点 和 其father
    int dir;
    BtNode<T>* father = findnode(elmt, &dir);
    // 没有查找到 直接返回
    if (!father) return false;

    BtNode<T>* del = father;                // 保存需要删除的节点，默认为root
    if (dir == -1) del = father->llink;     // 需要删除的节点在其父节点 左边
    else if (dir == 1) del = father->rlink; // 需要删除的节点在其父节点 右边

    // 1. 没有右子树，左右子树都没有也在这里处理
    //              x
    //          del
    //      x
    //  x       x
    if (!del->rlink) {
        if (del == root) {      // 根节点，则直接指向llink
            root = root->llink;
        } 
        else {                  // 非根节点，
            if (dir == 1)
                father->rlink = del->llink;  // ？？？ 上一节点的l or r
            else    
                father->llink = del->llink;  // ？？？ 上一节点的l or r
        }
        delete del;
        --theSize;
        return true;
    }
    // 2. 没有左子树
    //  x
    //      del
    //          x
    //      x       x
    if (!del->llink) {
        if (del == root) {
            root = root->rlink;
        } 
        else {
            if (dir == 1) 
                father->rlink = del->rlink;
            else 
                father->llink = del->rlink;
        }
        delete del;
        --theSize;
        return true;
    }
    // 3. 左右子树都有
    //  x
    //    \
    //     del
    //    /    \
    //   x       x
    //    \       \
    //     x       x    
    if (del->llink && del->rlink) {
        // 3.1 查找其左子树中最大节点
        BtNode<T>* prev = del;
        BtNode<T>* p = del->llink;  // 左子树中找最大的
        while (p->rlink) {          // 选择合适的节点代替，左子树中找最大的
            prev = p;               // 保存上个节点的指针
            p = p->rlink;           // 继续找右子节点
        }                           // p为选择的左子树最大的节点，prev为其父节点
        // 3.2 拷贝此节点数据到del
        del->data = p->data;                // 将最大节点的数据 拷到 del->data
        // 3.3 修改链接关系
        // 3.3.1 最大结点就是其左第一个
        if (prev == del)                    // 最大节点就是其左节点，肯定p无rlink, del的llink就是p的llink
            del->llink = p->llink;          // 本来就是找的左子树，所以还是link到del的左
        // 3.3.2 最大结点不是其左第一个
        else                                // 最大节点不是del的llink，，那一定是prev的rlink
            prev->rlink = p->llink;         // ? p->rlink; or p->llink; 源码->rlink错误，应该是->llink，
                                            // 因为p是选择的最大节点，p的rlink一定是nullptr，llink才有存在子树的可能。
        // 3.4 删除
        delete p;   // 左子树最大节点数据已经拷贝到del数据中，应该释放掉p
        --theSize;
    }
    return true;
}
// 查找节点
// 返回值是父节点指针，dir是找到节点所属父节点的方向
//  返回nullptr 没找到
// *dir  0根节点 -1左子节点 1右子节点
template<typename T>
BtNode<T>* BinTree<T>::findnode(const Element<T>& elmt, int* dir)
{
    BtNode<T>* fathernode = root;   // 保存其父节点，从根节点开始找，根节点为父节点
    BtNode<T>* p = root;            // 索引指针，从根节点开始找
    *dir = 0;                       // dir返回该节点所属父节点的l or r link
    while (p) {
        if (p->data.key == elmt.key) return fathernode; 
        fathernode = p;
        if (elmt.key > p->data.key) {
            p = p->rlink;
            *dir = 1;
        } else {
            p = p->llink;
            *dir = -1;
        }
    }
    return nullptr;
}

template<typename T>
void BinTree<T>::inorder() const 
{
    inorder(root);
    cout << endl;
}
// 中序遍历用递归，打印数据
template<typename T>
void BinTree<T>::inorder(BtNode<T>* n) const 
{
    if (n) {
        inorder(n->llink);
        cout << n->data.key << " ";
        inorder(n->rlink);
    }
}
// 层序遍历
//  需要queue，打印--左右子节点存在入队列--queue为空则返回--不为空取出节点
template<typename T>
void BinTree<T>::levelorder() const
{ levelorder(root); }
template<typename T>
void BinTree<T>::levelorder(BtNode<T>* n) const
{
    BtNode<T>* p = n;
    list_queue<BtNode<T>*> queue;
    while (p) {
        cout << p->data.key << " "; 
        if (p->llink) queue.push(p->llink);    
        if (p->rlink) queue.push(p->rlink);
        if (queue.empty()) {
            cout << endl;
            return; // 没有了就返回。queue在这里最多存3个元素
        }
        p = queue.front();
        queue.pop();
    }
}    
// 根节点的序号为1，从root开始显示
template<typename T>
void BinTree<T>::display() const 
{ if (root) root->display(1); };

template<typename T>
unsigned long BinTree<T>::size() const
{ return theSize; }

// ----------------------------------------------


int main()
{

    BinTree<string> bt;
    // 第一个树
    bt.insert(Element<string>(30, "aa"));
    bt.insert(Element<string>(20, "aa"));
    bt.insert(Element<string>(38, "aa"));
    bt.insert(Element<string>(3, "aa"));
    bt.insert(Element<string>(10, "aa"));
    bt.insert(Element<string>(24, "aa"));
    bt.insert(Element<string>(8, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();
//                                30
//                             /      \
//                          20         38
//                        /   \
//                      3       24     
//                    /   \  
//                  8      10   
    bt.erase(Element<string>(24, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();        
    bt.erase(Element<string>(20, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();
    bt.erase(Element<string>(3, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();
    bt.erase(Element<string>(10, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder(); 
    bt.erase(Element<string>(30, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();    
    bt.erase(Element<string>(38, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder(); 
    bt.erase(Element<string>(8, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();   
    
    // 第二个树 
    bt.insert(Element<string>(20, "aa"));
    bt.insert(Element<string>(15, "aa"));
    bt.insert(Element<string>(25, "aa"));
    bt.insert(Element<string>(7, "aa"));
    bt.insert(Element<string>(18, "aa"));
    bt.insert(Element<string>(6, "aa"));
    bt.insert(Element<string>(17, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();   
//                  20
//                /    \
//              15      25
//            /    \
//          7       18
//        /        /
//      6       17
    bt.erase(Element<string>(20, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();        
    bt.erase(Element<string>(6, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();
    bt.erase(Element<string>(18, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();
    bt.erase(Element<string>(25, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder(); 
    bt.erase(Element<string>(17, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();    
    bt.erase(Element<string>(7, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder(); 
    bt.erase(Element<string>(15, "aa"));
    cout << "size: " << bt.size() << "  "; bt.inorder();   
 
//  stdout
    // size: 7  3 8 10 20 24 30 38 
    // size: 6  3 8 10 20 30 38
    // size: 5  3 8 10 30 38 
    // size: 4  8 10 30 38
    // size: 3  8 30 38
    // size: 2  8 38
    // size: 1  8
    // size: 0
    // size: 7  6 7 15 17 18 20 25
    // size: 6  6 7 15 17 18 25
    // size: 5  7 15 17 18 25
    // size: 4  7 15 17 25
    // size: 3  7 15 17
    // size: 2  7 15
    // size: 1  15
    // size: 0
    return 0;
}