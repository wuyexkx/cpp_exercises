#include <iostream>
#include <algorithm>
#include <vector>
#include <typeinfo>
using namespace std;

// 仿函数的可适配条件 （一般仿函数用在Algorithm中）
//      无非是使用那些操作符，一元或者二元的，unary_function binary_function
// 一般写仿函数都是直接写，没有继承关系
//      没有继承关系这个仿函数就没有融入到STL体系中
//      在继承关系中不一定是为了继承data和方法，也有继承typedef的
//      对于这种继承（父类只有typedef的）只有好处，不占内存
// 
//      所以如果希望仿函数能够被适当调整 就要去继承相应的父类
//      希望仿函数能够回答适配器的一些问题（算法会问迭代器一些问题）

// 适配器（适配器A要去改造B，A对外可见，A内部调用B。 适配器是一个桥梁）通过继承或内含
//      仿函数适配器  容器适配器  迭代器适配器
//   如：
//      容器适配器之stack、queue 的底部用的都是deque
//      函数适配器之bind2nd，


// 函数适配器之bind2nd
//   1. count_if
template<class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
Count_if(InputIterator first, InputIterator last, Predicate pred)
{
    cout << "Predicate type: " << typeid(pred).name() << endl;
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first)
    {
        if(pred(*first))
            ++n;
    }
    return n;
}
//   2. Binder2nd 绑定操作的第二个参数，使其看上去为一元操作
template<class Operation>
class Binder2nd // 继承之后就可以回答问题了
: public unary_function<typename Operation::first_argument_type, typename Operation::result_type>
{
public:
    Binder2nd(const Operation& x, const typename Operation::second_argument_type& y) // Operation的第二个参数是必须给定的
    : op(x), value(y) { }
    typename Operation::result_type operator()(const typename Operation::first_argument_type x) 
    { // Binder2nd<less<int>>(less<int>(), 3);                                       // Operation的第一个参数是自动赋给的
        return op(x, value); // less是一个struct，最终调用的是less的(), 所以这里也要重载()
    }
protected:
    Operation op;
    typename Operation::second_argument_type value; // value的类型也要问出来
};
//   3. Bind2nd辅助函数
template<class Operation, class T>
inline Binder2nd<Operation> Bind2nd(const Operation op, const T& x)
{
    typedef typename Operation::second_argument_type arg2_type; // Operation需要回答问题，第二个实参的类型
    return Binder2nd<Operation>(op, arg2_type(x)); // 第二个参数类型转换
}


int main()
{
    vector<int> v1{1,2,3,4,1,3,1,3,2};
    // int i = Count_if(v1.begin(), v1.end(), [](int a){ return a > 3; } );
    // cout << "count: " << i << endl;

    cout << Count_if(v1.begin(), v1.end(), Bind2nd(less<int>(), 2)) << endl;
    // cout << Count_if(v1.begin(), v1.end(), Binder2nd<less<int>>(less<int>(), 2)) << endl;
    
    return 0;
}

