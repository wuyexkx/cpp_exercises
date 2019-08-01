#include <iostream>
#include <vector>
using namespace std;

// 我的博客 https://mp.csdn.net/mdeditor/98068903#

// 对象模型: 关于虚指针(vptr)和虚表(vtbl)

class A
{
public:
    void func1() {}
    virtual void func2() { }
private:
    int m_data1;
};

int main()
{
    cout << sizeof(A) << endl;
    return 0;
}
