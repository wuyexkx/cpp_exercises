#include<iostream>
#include<queue>
using namespace std;

template<typename T>
class BinTree
{
// private:
public:
    struct Node
    {
        Node(const T& d=T(), Node* l=nullptr, Node* r=nullptr)
        : data(d), llink(l), rlink(r) { }
        T data;
        Node* llink;
        Node* rlink;
    };    
    Node* root;

    // 前序遍历，lll(从上往下) -- rrr(从下往上)
    void pre_order() const
    { pre_order(root); }
    void pre_order(const Node* n) const
    {
        if (n) {
            cout << n->data << " "; 
            pre_order(n->llink);
            pre_order(n->rlink);
        }
    }    
    // 中序遍历，有序的，由小到大
    void in_order() const
    { in_order(root); }
    void in_order(const Node* n) const
    {
        if (n) {
            in_order(n->llink);
            cout << n->data << " "; 
            in_order(n->rlink);
        }        
    }    
    // 后序遍历
    void post_order() const
    {
        post_order(root);
    }  
    void post_order(const Node* n) const
    {
        if (n) {
            post_order(n->llink);
            post_order(n->rlink);
            cout << n->data << " "; 
        }                
    }               
    // 层序遍历
    void level_order() const
    {
        Node* current = root;
        queue<Node*> q_node;            
        while (current) {
            cout << current->data << " ";
            if (current->llink) 
                q_node.push(current->llink);
            if (current->rlink) 
                q_node.push(current->rlink);   
            if (q_node.empty()) return;         
            current = q_node.front();
            q_node.pop();    
        }
    }    

public:
    BinTree(Node* n=nullptr)
    : root(n) { }
};

int main()
{ 
    BinTree<char>::Node a('1');
    BinTree<char>::Node b('2');
    BinTree<char>::Node c('3');
    BinTree<char>::Node d('4');
    BinTree<char>::Node aa('a');
    BinTree<char>::Node bb('b');
    BinTree<char>::Node cc('c');

    a.llink = &b;
    b.llink = &c;
    c.llink = &d;
    a.rlink = &aa;
    b.rlink = &bb;
    c.rlink = &cc;
    BinTree<char> bt(&a);

//              1
//            /   \
//          2       a
//        /   \  
//      3       b
//    /   \
//  4       c
    bt.pre_order(); cout << endl;
    bt.in_order();  cout << endl;
    bt.post_order();cout << endl;
    bt.level_order();
// stdout
    // 1 2 3 4 c b a 
    // 4 3 c 2 b 1 a 由小到大顺序
    // 4 c 3 b 2 a 1
    // 1 2 a 3 b 4 c
    return 0;
}