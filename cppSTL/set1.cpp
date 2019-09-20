#include <iostream>
#include <set>
#include <string>
#include <cstdio>
#include <ctime>
using namespace std;

// 都适合频繁搜索查找的情况（红黑树，hash）
// set/multiset插入较慢，但是查找很快 (红黑树)
// map/multimap有key-value, (红黑树)
// unordered_multiset (hash), 当元素>=篮子时，篮子扩充
// unordered_multimap 

string get_a_targetStrings()
{
long target = 0;
char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
}

void set_test(long& num)
{
std::set<string> s; // 不允许重复，key就是value
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<num; ++i)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            s.insert(string(buf)); // 存在重复元素，因为set不重复，所以插入的元素个数小于num
        }
        catch(const std::exception& e)
        {
            std::cerr << "i=" << i << " " << e.what() << endl;
        }      
    }
    cout << " insert time: " << clock() - timeStart << " ms" << endl;
    cout << "    set.size: " << s.size() << endl;
    cout << "set.max_size: " << s.max_size() << endl;
    cout << "*set.begin(): " << *s.begin() << endl;

    // 查找
string target = get_a_targetStrings();
    timeStart = clock();
    auto pItem = s.find(target);
    if(pItem != s.end())
        cout << "multiset.find: " << *pItem << endl;
    else
        cout << "not find." << endl;
    cout << "      multiset.find: " << clock() - timeStart << " ms" << endl;   
}


int main()
{
    long num = 500000;
    set_test(num);
    return 0;
}