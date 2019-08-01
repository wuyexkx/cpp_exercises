#include <iostream>
#include <vector>
using namespace std;

/*
用法:
for(decl : coll) // coll为容器
{
    statement
}
*/

int main()
{
    for(int i : {1, 2, 3, 4, 5})
    {
        cout << i << " ";
    }

    cout << endl;

    vector<int> vec{1,2,3,4,5};
    for(auto elem : vec)  // pass by value
    {
        cout << elem << " ";
    }

    cout << endl;

    for(auto& elem : vec) // pass by reference
    {
        elem *= 3; // vec元素被改变
    }
    for(auto elem : vec) cout << elem << " ";

    return 0;
}
