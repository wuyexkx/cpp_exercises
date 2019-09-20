#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <unordered_set>
using namespace std;

// associative container 关联容器  （红黑树，hash）
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

void unordered_multiset_test(long& num)
{
std::unordered_multiset<string> um_s; // 允许重复，key就是value
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<num; ++i)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            um_s.insert(string(buf));
        }
        catch(const std::exception& e)
        {
            std::cerr << "i=" << i << " " << e.what() << endl;
            abort();
        }      
    }
    cout << "                insert time: " << clock() - timeStart << " ms" << endl;
    cout << "    unordered_multiset.size: " << um_s.size() << endl;
    cout << "unordered_multiset.max_size: " << um_s.max_size() << endl;
    cout << "*unordered_multiset.begin(): " << *um_s.begin() << endl;
    cout << "\n    unordered_multiset.bucket_count: " << um_s.bucket_count() << endl;
    cout << "     unordered_multiset.load_factor: " << um_s.load_factor() << endl;
    cout << " unordered_multiset.max_load_factor: " << um_s.max_load_factor() << endl;
    cout << "unordered_multiset.max_bucket_count: " << um_s.max_bucket_count() << endl;

    cout << endl;
    for(unsigned i=0; i<20; ++i) // 查看前20个bucket的目前大小
    {
        cout << "bucket #" << i << " has " << um_s.bucket_size(i) << " elements." << endl;
    }

    // 查找
string target = get_a_targetStrings();
    timeStart = clock();
    auto pItem = um_s.find(target);
    if(pItem != um_s.end())
        cout << "unordered_multiset.find: " << *pItem << endl;
    else
        cout << "not find." << endl;
    cout << "      unordered_multiset.find: " << clock() - timeStart << " ms" << endl;   
}

int main()
{
    long num = 500000;
    unordered_multiset_test(num);

    return 0;
}