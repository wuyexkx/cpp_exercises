#include <iostream>
using namespace std;

// 将 节点类 作为 私有的成员类
class List
{
public:
    void test();
    void show() const;
private:
    class Node
    {
    // private: // 如果嵌套中的类 包含private数据 那么在嵌套它的类里无法访问,只能在被嵌套的类中使用
    public:
        char data[3];
        Node* link;
    };
    Node* first;
};
void List::test()
{
    Node* f = new Node;
    f->data[0] = 'A';
    f->data[1] = 'B';
    f->data[2] = 'C';
    f->link = 0; // f可以访问link,因为link是 嵌套在 List中的 public数据.如果link为private则不行
    first = f;

    f = new Node;
    f->data[0] = 'D';
    f->data[1] = 'E';
    f->data[2] = 'F';
    f->link = 0;
    first->link = f;

    f = new Node;
    f->data[0] = 'G';
    f->data[1] = 'H';
    f->data[2] = 'I';
    f->link = 0;
    first->link->link = f;
}
void List::show() const
{
    cout << first->data << endl;
    cout << first->link->data << endl;
    cout << first->link->link->data << endl;
}

int main()
{
    List L;
    L.test();
    L.show();

    return 0;
}
