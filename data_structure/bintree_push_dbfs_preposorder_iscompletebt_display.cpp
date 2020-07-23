#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

struct node {
    node(int v = -1) { val = v; left = right = nullptr; }
    // 显示当前节点以及子节点的序号
    void display(int i) 
    {
        std::cout << i << ":" << val << " ";
        if (left) left->display(2 * i);
        if (right) right->display(2 * i + 1);
    }

    int val;
    node* left, *right;
};

class bin_tree {
public:
    bin_tree() { root = nullptr; }

    // 插入数据
    void push(int val) 
    {
        if (root == nullptr) {
            node* newnod = new node(val);
            root = newnod;
            return;
        }
        // 找到合适的位置，并保存父节点
        node* cur = root;  
        node* p = nullptr;      
        while (cur != nullptr) {
            // 不存在相等的情况
            if (cur->val == val) return;
            p = cur;
            if (val > cur->val) 
                cur = cur->right;
            else if (val < cur->val) 
                cur = cur->left;
        }
        // 找到了，都是放在叶子节点
        node* newnod = new node(val);
        if (val > p->val) {
            p->right = newnod;
        } else {
            p->left = newnod;
        }
    }
    
    // 显示节点序号
    void display() const { root->display(1); std::cout << std::endl; };

    // 广度遍历
    void bfs() const
    {
        queue<node*> ndque;
        ndque.push(root);
        while (!ndque.empty()) {
            node* tmp = ndque.front();
            ndque.pop();
            std::cout << tmp->val << " ";
            if (tmp->left != nullptr) ndque.push(tmp->left);
            if (tmp->right != nullptr) ndque.push(tmp->right);
        }
        std::cout << std::endl;
    }

    // 深度优先遍历
    void dfs() const
    { dfs(root); std::cout << std::endl; }
    void dfs(node* nd) const
    {
        if (nd->left) dfs(nd->left);
        std::cout << nd->val << " ";
        if (nd->right) dfs(nd->right);
    } 
    void pre() const
    { pre(root); std::cout << std::endl; }
    void pre(node* nd) const
    {
        std::cout << nd->val << " ";
        if (nd->left) pre(nd->left);
        if (nd->right) pre(nd->right);
    }
    void pos() const
    { pos(root); std::cout << std::endl; }
    void pos(node* nd) const
    {
        if (nd->left) pos(nd->left);
        if (nd->right) pos(nd->right);
        std::cout << nd->val << " ";
    }

// private:
    node* root;
};


// 完全
bool iscomplete_bt(const bin_tree& pbt)
{
    // 广度遍历 并存入null节点
    // 广度优先遍历完全二叉树时，遇到null说明结束，
    // 若结束后队列还有非null的节点，则非完全二叉树
    queue<node*> ndque;
    ndque.push(pbt.root);
    while (ndque.front() != nullptr) {
        node* tmp = ndque.front();
        ndque.pop();
        ndque.push(tmp->left);
        ndque.push(tmp->right);
    }
    while (!ndque.empty()) {
        node* tmp = ndque.front();
        ndque.pop();
        if (tmp != nullptr)
            return false;
    }
    return true;
}


int main()
{
    bin_tree bt;
    bt.push(6);
    bt.push(4);
    bt.push(8);
    bt.push(2);
    bt.push(5);
    bt.push(7);
    // bt.push(1);

    cout << "dis: "; bt.display();
    cout << "bfs: "; bt.bfs();
    cout << "dfs: "; bt.dfs();
    cout << "pre: "; bt.pre();
    cout << "pos: "; bt.pos();
    std::cout << iscomplete_bt(bt) << std::endl;

    // dis: 1:6 2:4 4:2 5:5 3:8 6:7 
    // bfs: 6 4 8 2 5 7 
    // dfs: 2 4 5 6 7 8 
    // pre: 6 4 2 5 8 7 
    // pos: 2 5 4 7 8 6 
    // 1

    return 0;
}