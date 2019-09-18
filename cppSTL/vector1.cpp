#include <iostream>
#include <vector>
#include <stdexcept>
#include <string.h> // strcmp
#include <string>
#include <cstdlib> // abort()
#include <cstdio>  // snprintf()
#include <ctime>
#include <algorithm>
#include <stdlib.h>
using namespace std;

// vector可以往后扩展，但是每次扩展容量是*2。 一般往后添加元素

string get_a_target_string()
{
    long target = 0;
    char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    // snprintf(), 将参数转化成字符串，“%d”为格式控制，"%09d"共9位，不足就补0。第二个参数为长度，多了剪掉
    snprintf(buf, 10, "%d", target);
    return string(buf); // 转化成string类型
}
int compareStrings(const void* a, const void* b)
{
    if( *(string*)a > *(string*)b )
        return 1;
    else if( *(string*)a < *(string*)b )
        return -1;
    else
        return 0;
}

void vector_test(long& value)
{
vector<string> c;
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<value; ++i)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        }    
        catch(exception& p)
        {
            cout << "i=" << i << " " << p.what() << endl;
        }
    }
    cout << "      push time: " << clock() - timeStart << "ms" <<  endl;
    cout << "    vector.size: " << c.size() << endl;
    cout << "   vector.front: " <<c.front() << endl;
    cout << "    vector.back: " << c.back() << endl;
    cout << "    vector.data: " << c.data() << endl;
    cout << "vector.capacity: " << c.capacity() << endl;

    cout << endl;
    string target = get_a_target_string();
    // 直接使用顺序查找
    {
        timeStart = clock();
    auto pItem = ::find(c.begin(), c.end(), target); // ::find属于全局的模板函数
        if(pItem != c.end())
            cout << "::find: " << *pItem << endl;
        else
            cout << "not found!" << endl;
        cout << "::find time: " << clock() - timeStart << " ms" << endl;        
    }
    // 先用qsort(), 再bsearch()
    {
        timeStart = clock();
        // qsort(c.data(), c.size(), sizeof(string), compareStrings); //有问题, 运行报错
        sort(c.begin(), c.end());
    string* pItem = (string*)bsearch(&target, c.data(), c.size(), sizeof(string), compareStrings);
        if(pItem != NULL)
            cout << "bsearch: " << *pItem << endl;
        else
            cout << "not found." << endl;
        cout << "qsort + bsearch time: " << clock() - timeStart << " ms" << endl;
    }
}

int main()
{
    long num = 500000;
    vector_test(num);

    return 0;
}
