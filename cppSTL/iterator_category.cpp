#include <iostream>
#include <iterator>
#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <set>
#include <map>
// #include <multiset> // 世界上没有这个东西，在对应的set或map里边
// #include <multimap>
#include <unordered_set>
#include <unordered_map>
// #include <unordered_multiset> // 世界上没有这个东西，在对应的set或map里边
// #include <unordered_multimap>
#include <typeinfo>
using namespace std;

// algorithm对容器一无所知，是通过iterator建立关系的，所以algorithm需要的信息会去从iterator那里找答案
//      category是迭代器的类型，可以怎么“走”，总共只有5类iterator_category. 然而并没有用1,2,3来表示
//      是用class来表现的，用对象来表现
// 
// 

void _dispaly_catgory(input_iterator_tag)
{ cout << "input_iterator_tag" << endl; }
void _diaplay_catgory(output_iterator_tag)
{ cout << "output_iterator_tag" << endl;}
void _diaplay_catgory(forward_iterator_tag)
{ cout << "forward_iterator_tag" << endl; }
void _dispaly_category(bidirectional_iterator_tag)
{ cout << "bidirectional_iterator_tag" << endl; }
void _display_category(random_access_iterator_tag)
{ cout << "random_access_iterator_tag" << endl; }

template<class I>
void display_category(const I& iter) // 这里的参数没有用，主要是得到template I
{
typedef typename std::iterator_traits<I>::iterator_category cagy;   
    // _display_category(cagy); // // 将I丢入萃取机得到其iterator的category ,,error 类型无法相互转换
    cout << "typeid(iter).name()= " << typeid(iter).name() << endl;
}

int main()
{
    cout << "\nTest iterator_category()....." << endl;

    display_category(array<int, 10>::iterator()); // 里边产生一个临时iterator对象
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(deque<int>::iterator());

    display_category(set<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(multiset<int>::iterator());
    display_category(multimap<int, int>::iterator());

    display_category(unordered_set<int>::iterator());
    display_category(unordered_map<int, int>::iterator());
    display_category(unordered_multiset<int>::iterator());
    display_category(unordered_multimap<int, int>::iterator());

    display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout, ""));

    return 0;
}
