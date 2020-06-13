#if 0
CC="g++"
filename="$0"
name="${filename%.*}"
$CC -o $name $filename 
$name $@
rm $name
exit
#endif


#include <iostream>
#include <map>
#include <string>
#include <vector>
#include<algorithm>

using namespace std;

#define PAIR pair<char, int> 


// 比较的规则，可以用like-function的class 也可以是正儿八经的function
// 就是函数对象了，less和greater是stl里面的函数对象
// 实质是对operator()操作符的重载
struct compval {
    bool operator() (PAIR& lhs,PAIR& rhs)
    {
        return lhs.second < rhs.second;
    }
};
// bool compval(PAIR& lhs,PAIR& rhs)
// {
//     return lhs.second < rhs.second;
// }


int main()
{
    // 1. 默认按key升序排序，可以修改成降序 greater<Key>
    map<char, int> map1; // class Compare = less<Key> ，默认值 less<Key>，可以改降序greater<Key>
    map1.insert({('a'), 1});
    map1.insert({('c'), 2});
    map1.insert({('e'), 4});
    map1.insert({('b'), 5});
    map1.insert({('d'), 3});    
    for (auto m : map1)
        cout << m.first << "-" << m.second << " ";
    cout << endl;
    map<char, int, greater<char>> map2(map1.begin(), map1.end()); // 用迭代器构造一个新的map，按找key降序排列
    for (auto m : map2)
        cout << m.first << "-" << m.second << " ";


    cout << endl << endl;
    // 2. map没有对value排序的方法，可以通过vecotr存储pair，在vecotr中自己写compare函数对pair的second排序
    vector<PAIR> vct;
    for (const auto &m : map1) {
        vct.push_back(m);
    }
    sort(vct.begin(), vct.end(), compval());
    for (auto v : vct) 
        cout << v.first << "-" << v.second << " ";

// stdout:
    // a-1 b-5 c-2 d-3 e-4 
    // e-4 d-3 c-2 b-5 a-1 

    // a-1 c-2 d-3 e-4 b-5

    cout << endl;
    return 0;
}