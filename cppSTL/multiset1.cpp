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

void multiset_test(long& num)
{
std::multiset<string> m_s; // 允许重复，key就是value
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<num; ++i)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            m_s.insert(string(buf));
        }
        catch(const std::exception& e)
        {
            std::cerr << "i=" << i << " " << e.what() << endl;
        }      
    }
    cout << "      insert time: " << clock() - timeStart << " ms" << endl;
    cout << "    multiset.size: " << m_s.size() << endl;
    cout << "multiset.max_size: " << m_s.max_size() << endl;
    cout << "*multiset.begin(): " << *m_s.begin() << endl;

    // 查找
string target = get_a_targetStrings();
    timeStart = clock();
    auto pItem = m_s.find(target);
    if(pItem != m_s.end())
        cout << "multiset.find: " << *pItem << endl;
    else
        cout << "not find." << endl;
    cout << "      multiset.find: " << clock() - timeStart << " ms" << endl;   
}


int main()
{
    long num = 500000;
    multiset_test(num);
    return 0;
}