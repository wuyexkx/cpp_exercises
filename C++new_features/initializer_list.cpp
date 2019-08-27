#include <iostream>
#include <algorithm>
using namespace std;

class P
{
public:
    P(int a, int b)                   // (1)
    {
        cout << "P(int a, int b)\n";
    }
    P(initializer_list<int> initlist) // (2)   传入一包同类型数据,个数任意
    {
        cout << "P(initializer_list<int> initlist)\n";
        for(auto i : initlist)
            cout << i << " ";
        cout << endl;
    }
};

int main()
{
    P p1(77, 5);
    P p2{77, 5}; // 如果没有(2), 编译器会拆解为两个参数 再去调用(1)
    P p4 = {77, 5}; // 同上行
    P p3{77, 5, 42};

// output:
    // P(int a, int b)
    // P(initializer_list<int> initlist)
    // 77 5 
    // P(initializer_list<int> initlist)
    // 77 5 
    // P(initializer_list<int> initlist)
    // 77 5 42 

    cout << max({1,2,3,4,1,434,2323,24343,5565,33232,-34,343,9999}) << endl;

return 0;
}
