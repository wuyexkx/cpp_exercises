#include <iostream>
#include <vector>

using namespace std;

// 递归算法，算阶乘。
// 递归缺点：所有中间过程都需要暂存，数据量大。往回走的时候会利用暂存数据
// 优点：结构清晰，容易理解
long factorial(const int x)
{
    if(x == 0) return 1; // 阶乘最后是 返回 0的阶乘为1
    else return x * factorial(x-1);
}
// 迭代算法。所有递归都可以用迭代完成
long iteration(const int x)
{
    int rst = 1;
    for(int i=x; i>0; i--)
        rst = rst * i;
    return rst;
}


int main()
{

    cout << iteration(5) << endl;
    cout << factorial(4) << endl;
    return 0;
}
