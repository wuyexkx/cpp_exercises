#ifndef __TEST_H
#define __TEST_H

template<class T> 
class list_iterator;

// ==========================Node====================================
template<class T>
struct Node
{
    Node(const T& dt = T())
    : link(nullptr), data(dt)
    { }
    Node<T>* link;
    T data;
};

// =============================list=================================
template<class T>
class List
{
    friend class list_iterator<T>;
    typedef list_iterator<T> iter;
public:
    List()
    : first(nullptr) { }
    ~List()
    {
        while(!is_empty()) 
        {
            auto temp = first;
            first = first->link;
            // ~(temp->data);
            delete temp;
        }
    }
    void push_front(const T& it);
    bool is_empty() const;
    void print() const;
    iter begin()    // 通过begin将 list 和 其迭代器 联系起来， 返回值是迭代器
    {
        Node<T>* n = first;
        return iter(n); // 首节点放入迭代器
    }
    iter end() { return iter(nullptr); }

private:
    Node<T>* first;
};
template<class T>
void List<T>::push_front(const T& it)
{
    Node<T>* newNode = new Node<T>(it);
    if(!is_empty())
        newNode->link = first;
    first = newNode;
 }
template<class T>
bool List<T>::is_empty() const
{
    return first == nullptr;
}
template<class T>
void List<T>::print() const
{
    Node<T>* crt = first;
    while(crt != nullptr)
    {
        std::cout << crt->data;
        if(crt->link) std::cout << " " << "->" << " ";
        crt = crt->link;
    }
    std::cout << std::endl;
}

// ===================list所对应的迭代器=============================
template<class T>
class list_iterator
{
    typedef list_iterator self;
public:
    list_iterator(Node<T>* n) // 为迭代器内部的Node指针初始化
    : node(n) { }

    T& operator* ()
    {
        if(node)
            return node->data;
        std::cerr << "this iterator is null." << std::endl;
    }

    self& operator++ () // ++i 返回值引用
    {
        if(node) node = node->link;
        return  *this;       
    }
    self operator++ (int) // i++ 返回新对象， int用于区分前++
    {
        self l_it = *this;
        if(node)
            node = node->link;
        return l_it;
    } 

    bool operator!= (const list_iterator<T>& l_it)
    {
        return this->node != l_it.node; // node已经是指针了
    }
    
    Node<T>* node;
};


#endif