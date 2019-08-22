#include <iostream>
#include "binary_search_tree.h"
using namespace std;

/*
二叉查找树(BST, binary search tree)
性质:
    1.每个元素都有一个键值, 而且不允许重复
    2.左子树的键值 都小于 跟节点的键值
    3.右子树的键值 都大于 跟节点的键值
    4.左右子树都是二叉查找树
当插入的数据是由大到小, 那么二叉查找树变成了链表, 无法实现快速的二分查找
如果存在一种自动平衡分支的树,那么就很完美了--->红黑树
*/

/*
        5
      4   6
    2
      3
*/
int main()
{
    // ----测试display(), 显示节点和子节点的位置 和 key----
    Node<int> a;
    Node<int> b;
    Node<int> c;
    Node<int> d;
    Node<int> e;

    a.data.key = 5;
    b.data.key = 4;
    c.data.key = 2;
    d.data.key = 6;
    e.data.key = 3;

    a.llink = &b;
    a.rlink = &d;
    b.llink = &c;
    c.rlink = &e;

    a.display(1); 
    //-------------------------------------------------

    cout << "----------------------------\n";
    Element<int> aa{5};
    Element<int> bb{4};
    Element<int> cc{2};
    Element<int> dd{6};
    Element<int> ee{3};

    BST<int> bst;
    bst.Insert(aa);
    bst.Insert(bb);
    bst.Insert(cc);
    bst.Insert(dd);
    bst.Insert(ee);
    bst.display();

    cout << "\nrecursion result: " << bst.Search(dd)->data.key << endl;
    cout << "\n iterator result: " << bst.IterSearch(cc)->data.key << endl;

    cout << "   inOrder: ";  bst.InOrder();  cout << endl;


    return 0;
}
