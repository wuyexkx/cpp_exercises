#include <iostream>
#include <functional>
#include <bitset>
using namespace std;

// 1. 用于函数 
// ...就是一个所谓的包
// --------------------------这种写法必须并存-------------------------------
// 如果不写这个无参数的函数,将报错,error: no matching function for call to ‘print()’
// 因为递归到最后,后面的一包参数为空,传入的参数就是空,必须有函数与之对应
void print() { } 
// 模板参数为一个T 和一包Types  注意"..."的位置用法
template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args) //  接收 任意类型 的 任意个 参数
{
    cout << sizeof...(args) << " "; // 通过sizeof...可以知道后面pack参数的个数
    cout << firstArg << endl; // 输出第一个参数
    print(args...); // 递归, 第一次到这里会把参数分为 1个 和 一小包, 一直分到最后传入参数为空 去调用那个空参数函数
}
// -----------------------------------------------------------------------


// 2. 用于类
template<typename T>
inline void hash_combine(size_t& seed, const T& val) // (4) 
{
    seed ^= std::hash<T>()(val) + 0x9e3779b9
            + (seed<<6) + (seed>>2);
}
template<typename T>
inline void hash_val(size_t& seed, const T& val)     // (3)   参数(1, 2)
{
    hash_combine(seed, val);
}
template<typename T, typename... Types>
inline void hash_val(size_t& seed,
                const T& val, const Types&...args)   // (2)   参数(1, 2, pack)
{
    hash_combine(seed, val); // 调用(4)
    hash_val(seed, args...); // pack里还剩下一个参数,,所以会调用(3),  如果此时pack里参数多余两个, 将递归调用自己(2)直到pack还剩1个
}
template<typename... Types>
inline size_t hash_val(const Types&... args)         // (1)   参数(pack)
{
    size_t seed = 0;
    hash_val(seed, args...); // 调用(2), 因为第一个参数特化为size_t, 后面pack被分解成 val + pack
    return seed;
}
class Customer
{
public:
    string fname;
    string lname;
    int no;
};
class CustomerHash
{
public:
    std::size_t operator() (const Customer& c) const
    {
        return hash_val(c.fname, c.lname, c.no);   // 调用hash_val 
    }
};
/*
    在return调用hash_val()函数时:
    1. 首先调用(1), 因为传入的第一个参数类型 与 (2)不匹配
    2. 在(1)的内部调用(2), 因为第一个参数特化为size_t
    3. 在(2)的内部首先调用(4), 再调用(3)因为此时pack还剩下一个参数
*/

int main()
{
    print(7.5, "hello!", bitset<16>(15), 100); // bitset类一定重载了<<操作符
    // output:
    // 7.5
    // hello!
    // 0000000000001111
    // 100



    return 0;    
}