#include <iostream>
#include <ctime>
#include <array>
#include <cstdlib>
using namespace std;

long get_a_target_long()
{
    long target = 0;
    cout << "target (0~" << RAND_MAX << "): "; // 最大的随机数
    cin >> target;
    return target;
}
string get_a_target_string()
{
    long target = 0;
    char buf[10];
    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    // snprintf(), 将参数转化成字符串，“%d”为格式控制，"%09d"共9位，不足就补0。第二个参数为长度，多了剪掉
    snprintf(buf, 10, "%09d", target);
    return string(buf); // 转化成string类型
}
int compareLongs(const void* a, const void* b)
{
    return ( *(long*)a - *(long*)b );
}
int compareStrings(const void* a, const void* b)
{
    if( *(string*)a > *(string*)b )
        return 1;
    else if( *(string*) a < *(string*)b )
        return -1;
    else
        return 0;
}

#define ASIZE 500000
void array_test()
{
array<long, ASIZE> c;
clock_t timeStart = clock();
    for(long i=0; i<ASIZE; ++i)
    {
        c[i] = rand(); // rand()需要设置seed种子
    }
    cout << "push time(ms): " << clock() - timeStart << endl; // 保存ASIZE个随机数到array所需时间
    cout << " array.size(): " << c.size() << endl;
    cout << "array.front(): " << c.front() << endl;
    cout << " array.back(): " << c.back() <<endl;
    cout << " array.data(): " << c.data() << endl; //  array c的首地址，起点地址

long target = get_a_target_long();
    timeStart = clock();
    qsort(c.data(), ASIZE, sizeof(long), compareLongs); // 先排序。起始地址、元数个数、每个元素大小、排序规则

long* pItem = (long*)bsearch(&target, c.data(), ASIZE, sizeof(long), compareLongs); // 查询的目标、容器首地址、查找大小、每个元素大小、规则
    cout << "qsort()+bsearch(), time(ms): " << clock() - timeStart << endl;
    if(pItem != NULL)
        cout << "found: " << *pItem << endl;
    else
        cout << "not found!" <<endl;
}

int main()
{
    array_test();
    return 0;
}
