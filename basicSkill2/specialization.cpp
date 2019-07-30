#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 模板 泛化
template<class T>
struct hash1 
{
    size_t operator() (T x) const { return x+1; }
};

// 模板特化 
template<>
struct hash1<char>
{
    size_t operator() (char x) const { return x; }
};
template<>
struct hash1<int>
{
    size_t operator() (int x) const { return x; }
};
template<>
struct hash1<long>
{
    size_t operator() (long x) const { return x; }
};

int main()
{
    // hash1<long>()临时对象.  (1000)重载的()
    cout << hash1<long>() (1000) << endl; // output: 1000  指定模板特化

    cout << hash1<float>() (1000) << endl; // output: 1001 制定模板泛化

    return 0;
}

