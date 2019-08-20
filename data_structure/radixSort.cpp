#include <iostream>
#include <tuple>
#include <list>
using namespace std;

// 基数排序 简单 速度快 多一倍存储空间
// 基数: 如 10进制的基数为10 8进制的基数为8 对26个字母排序基数就是26 等等
// 最低位优先, 基数 == 链表的个数

void print(const list<int>& l)
{
    auto it = l.begin();
    while(it != l.end()) 
    { 
        cout << *it << " "; 
        it++; 
    }
     cout << endl;
}

template<typename T>
tuple<int, int> digits(const list<T>& l)
{
    auto it = l.begin();
    int ds = 10;
    int n = 1, num = 0;
    while(it != l.end()) // 遍历链表的所有数据
    {
        while(*it > ds)  // 找寻最大位数
        {
            ds *= 10;
            n++;
        }
        it++;
        num++;
    }
    return make_tuple(num, n);
}
template<typename T>
void radixSort(list<T>& l)
{
    auto t = digits(l);
    cout << "\nall nums: " << get<0>(t) << "  max digits: " << get<1>(t) <<  endl;

    list<T> lbuf[10]; // 十进制数,需要10个链表 存放个.十.百.千.位 比较的大小结果
    int ds = 10;      // 取出对应位的数字, 比较每一位时, 都对ds取余 ds为10 100 1000... 
    for( ; get<1>(t)>0; get<1>(t)--) // n位 排序n次
    {
        // 对应某位的数,存放在缓存中
        auto it = l.begin(); // 比较完某一位后l被改变,需要重新指向
        for( ; it != l.end(); it++)  // nums个数据
        {
            lbuf[*it % ds].push_back(*it);
        }

        // 从缓存中取出按某位排序后的数据, 放回原链表
        int n = 0;
        l.clear(); // 清空原链表
        while(n < 10) // 从缓存链表取出数据 刷新原链表
        {
            while(!lbuf[n].empty()) // 清空某个缓存链表
            {
                l.push_back(lbuf[n].front());
                lbuf[n].pop_front();
            }
            n++;
        }
        print(l);
        ds *= 10;
    }
}


int main()
{
    list<int> l{2, 51}; // 10个数
    
    print(l);
    
    radixSort(l);
    print(l);

    // cout << l.front() << endl;
    // l.pop_front();
    // it = l.begin();
    // while(it != l.end()) { cout << *it << " "; it++; } cout << endl;


    return 0;
}
