#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

auto l1 = []{
    cout << "lambda" << endl;
};

int main()
{
    int x = 0;
    int y = 42;
    auto l2 = [x, &y]() 
    {
        cout << x << endl; // 
        // cout << ++x << endl; // 不加mutable.  error: increment of read-only variable ‘x’
        cout << ++y << endl; // y为引用传入可以改变
    };  // 这个分号不能少,跟class的定义很像 
    x = 1;
    l2(); // 0  43 []是导入符号,所以在定义l2时 x 已经被导入


    int a = 0;
    int b = 42;
    auto l3 = [](int a, int b) // 参数就是常规操作了
    {
        cout << a << endl;  
        cout << ++b << endl; 
    };
    l3(a, b); // 0  43 


    vector<int> v{5, 28, 50, 10, 23, 10, 4, 6, 34, 102};
    int i = 10;
    int j = 100;
    v.erase(remove_if(v.begin(), 
                        v.end(), 
                        [i, j](int n){ return n < j && n > i; } ), // inline 定义规则, n由系统自动传递
                        v.end() ); // 第二个参数
    
    for(auto vv : v)
        cout << vv << " "; // 5 10 10 4 6 102 
    cout << endl;

    // output:
        // 0
        // 43
        // 0
        // 43
        // 5 10 10 4 6 102 

    return 0;
}
