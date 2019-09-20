#include <iostream>
#include <ctime>
#include <map>
#include <stdexcept>
#include <cstdio>
using namespace std;

long get_a_targetLong()
{
long target = 0;
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

// multimap不可以使用[0] [1], 放置的键可以重复
void multimap_test(long& num)
{
multimap<long, string> m_m;
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<num; i++)
    {
        try
        {
            snprintf(buf, 10, "%d", i); // rand()
            // multi和map的insert返回的东西不同， map::insert() 返回 pair<iterator, bool>，此处 bool 值表示插入操作是否成功
            m_m.insert(pair<long, string>(i, string(buf))); // 成对放置，key-value, insert会返回这个元素的iterator
        }
        catch(exception& e)
        {
            cout << "i=" << i << " " << e.what() << endl;
        }
    }
    cout << "insert time: " << clock() - timeStart << " ms" << endl;
    cout << "multimap.size: " << m_m.size() << endl;
    cout << "multimap.max_size: " << m_m.max_size() << endl;

    // 查找
long target = get_a_targetLong();
    timeStart = clock();
    auto pItem = m_m.find(target);
    if(pItem != m_m.end())
        cout << "multimap find: " << (*pItem).second << endl;
    else
        cout << "not find." << endl;
    cout << "multimap find time: " << clock() - timeStart << " ms" << endl;
}


int main()
{
    long num = 500000;
    multimap_test(num);

/*
    multimap<long, string> m;
    m.insert(pair<long, string>(1, "3434"));
    m.insert(pair<long, string>(1, "1111"));
    m.insert(pair<long, string>(3, "vfvf"));
    m.insert(pair<long, string>(2, "dfdf"));
    m.insert(pair<long, string>(1, "0909"));
    cout << "multimap.count: " << m.count(1) << endl;
    
    // 查找key相同的元素
    typedef multimap<long, string>::const_iterator mmp_it;
    pair<mmp_it, mmp_it> pair1 = m.equal_range(1); // 相同key对应的iter保存到pair
    for(auto it=pair1.first; it!=pair1.second; ++it)
        cout << it->second << " "; 
    cout << endl;
  */

    return 0;
}
