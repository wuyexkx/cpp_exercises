#include <iostream>
#include <list>
#include <stdexcept>
#include <cstdio>    // snprintf()
#include <ctime>     // clock()
#include <algorithm> // ::find()
using namespace std;

// list容器特指双向链表， forward_list单项链表

string get_a_targetStrings()
{
long target = 0;
char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%d", target);
    return string(buf);
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
void list_test(long& value)
{
list<string> c;
char buf[10];
clock_t timeStart = clock();
    for(long i=0; i<value; i++)
    {
        try
        {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        }
        catch(exception& p)
        {
            cout << "i=" << i << " " << p.what() << endl;
            abort();
        }
    }
    cout << "     push time: " << clock() - timeStart << " ms" << endl;
    cout << "     list.size: " << c.size() << endl;
    cout << " list.max_size: " << c.max_size() << endl;
    cout << "    list.front: " << c.front() <<endl;
    cout << "     list.back: " << c.back() <<endl;

    cout << endl;
    timeStart = clock();
    c.sort(); // 用list自带排序方法，用容器自带的算法最合适
    cout << "list.sort time: " << clock() - timeStart << " ms" << endl;
string target = get_a_targetStrings();
// string* pItem = (string*)bsearch(&target, &c, c.size(), sizeof(string), compareStrings); // 运行报错
    timeStart = clock();
auto pItem = ::find(c.begin(), c.end(), target);
    if(pItem != c.end())
        cout << "     ::find: " << *pItem << endl;
    else
        cout << "not found." << endl;
    cout << "::find time: " << clock() - timeStart << " ms" << endl;
}

int main()
{
    long num = 500000;
    list_test(num);
    return 0;
}
