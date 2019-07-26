#include <iostream>
using namespace std;

template<class T>
inline void 
swap1(T& a, T& b)
{
    T t = a;
    a = b;
    b = t;
}

// "abc"的排列组合
void permutations(char p[], const int st, const int end)
{
    if(st == end) // 输出一次结果
    {
        cout << p << endl;
    }
    else 
    {
        for(int i=st; i<=end; i++)
        {
            swap1(p[st], p[i]);
            permutations(p, st+1, end);
            swap1(p[st], p[i]);
        }
    }

    // // a开头
    // swap1(p[0], p[0]);
    // permutations(p, 1, 2);
    // swap1(p[0], p[0]);
    // // b开头
    // swap1(p[0], p[1]);
    // permutations(p, 1, 2);
    // swap1(p[0], p[1]);
    // // c开头
    // swap1(p[0], p[2]);
    // permutations(p, 1, 2);
    // swap1(p[0], p[2]);

}

int main()
{
    char p[] = "abcd";
    permutations(p, 0, 3);
}


