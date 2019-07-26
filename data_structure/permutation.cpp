#include <iostream>
using namespace std;

// "abc"的排列组合
void permutations(char p[], const int st, const int end)
{
    // 每次进入迭代都会判断 是否 第end-1个已经排好
    if(st == end) { cout << p << endl; } // 如果第end-1个已经排好，那么第end个就不用再排。直接输出
    else // 
    {
        for(int i=st; i<=end; i++)
        {
            swap(p[st], p[i]);  // 将 第st个元素 与 其往后第i个元素 交换
            permutations(p, st+1, end); // ****假设后面的元素已经递归好****
            swap(p[st], p[i]);  // 还原
        } 
    }
}
    // ----------帮助理解代码，假设字符 abc-------------

    // 以a开头，假设后面已经排好
    // swap(p[0], p[0]);
    // permutations(p, 1, 2); // 假设后面的元素已经递归好
    // swap(p[0], p[0]);

    // 以b开头，假设后面已经排好
    // swap(p[0], p[1]); // a跟b交换
    // permutations(p, 1, 2); 
    // swap(p[0], p[1]); // 如果 以b开头的 已经迭代输出完，那就复原刚交换的俩

    // 以c开头，假设后面已经排好
    // swap(p[0], p[2]); // a跟c交换
    // permutations(p, 1, 2);
    // swap(p[0], p[2]); // 如果 以c开头的 已经迭代输出完，那就复原刚交换的俩

int main()
{
    char p[] = "abc";
    permutations(p, 0, 2);

    // 输出结果：
    // abc
    // acb
    // bac
    // bca
    // cba
    // cab
}
