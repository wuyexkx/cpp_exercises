#include <iostream>
#include <vector>
#include <list>
using namespace std;

// 两个模板参数, 
// 第一个参数为T, 第二个参数为模板(此模板用到第一个参数T). 第二个模板参数跟第一个有关系
// 在使用的时候有弹性, (第二个参数为容器,需要指定容器元素的数据类型)这种效果必须用到模板模板参数
template<typename T, 
         template<typename T>
         class Container 
        >
class XCls
{
private:
    Container<T> c; // 构造Container对象 需要第一个模板参数T
};

template<typename T>
using Lst = list<T, allocator<T>>;

int main()
{

    // XCls<string, list> mylst1; // 因为容器本身还有第二第三模板参数,语法过不了
    XCls<string, Lst> mylst1; // (第二个参数为容器,需要指定容器元素的数据类型)这种效果必须用到模板模板参数

    return 0;
}

