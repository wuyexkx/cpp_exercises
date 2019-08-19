#include <iostream>
#include <list>

using namespace std;

void print(const list<int>& l)
{
    for(auto it = l.begin(); it !=l.end(); it++)  
        { std::cout << *it << " "; }
    std::cout << std::endl;
}

int main()
{
    cout << "\n------------添加数据--------------\n";
    list<int> l, l1;
    l.push_front(10);
    l.push_front(11);
    l.push_front(12);

    l.push_back(20);

    // 3个insert版本的重载
    // 1. 可以在中间插入数据    
    l.insert(l.begin(), 33);  // 第一参数为迭代器, 指定位置, 给出数据
    // 2. 可以插入多个相同数据
    l.insert(l.end(), 2, 22); // 第一参数为迭代器, 在末尾插入2个22
    print(l);

    l1.push_front(0);
    l1.push_front(1);
    l1.push_front(2);
    print(l1);

    // 3. 可以插入链表
    l.insert(l.begin(), l1.begin(), l1.end()); // 将l1完整 插入到 l的前面
    print(l);
    l.insert(l.end(), l1.begin(), l1.end());   // 将l1完整 插入到 l的后面
    print(l);

    auto it = l.begin();
    it++;
    l.insert(it, ++l1.begin(), --l1.end());
    print(l);

    cout << "\n---------删除数据------------\n";
    list<int> l2;
    l2.push_back(1);
    l2.push_back(2);
    auto positon0 = l2.insert(++l2.begin(), 0); // insert函数可以返回 此数据的迭代器
    auto positon1 = l2.insert(++(++(++l2.begin())), 11); 
    l2.push_back(3);
    l2.push_back(4);
    l2.push_back(5);

    print(l2);
    // 1. 删除一个
    l2.erase(positon0);
    print(l2);
    //2. 删除一堆
    l2.erase(l2.begin(), positon1); // 删除的区间 左闭右开 ***********************
    print(l2);

    cout << "\n----------反转排序-----------\n";
    list<int> l3;
    l3.push_back(0);
    l3.push_back(1);
    l3.push_back(2);
    l3.push_back(3);
    print(l3);

    l3.reverse(); // 反转
    print(l3);

    l3.sort(); // 排序 ,默认从小到大
    print(l3);


return 0;
}

