#ifndef __LINEAR_MAP_H
#define __LINEAR_MAP_H

#include <vector>

// 用vector做的一个简单的map, 线性的, 实际没什么用
template<class Key, class Value>
class LinearMap
{
public:
    LinearMap(const int size = 10)
    : arr(size), crtSize(0) { }
    void Put(const Key& k, const Value& v);
    Value Get(const Key& );
private:
    struct Data 
    {
        Data(const Key& k = Key(), const Value& v = Value()) // 初始值为T() 
        : key(k), value(v) { }
        Key key;
        Value value;
    };
    std::vector<Data> arr;
    int crtSize;
};
template<class Key, class Value>
void LinearMap<Key, Value>::Put(const Key& k,  const Value& v)
{
    arr[crtSize] = Data(k, v);
    crtSize++;
}
template<class Key, class Value>
Value LinearMap<Key, Value>::Get(const Key& k)
{
    int i = 0;
    while(i < crtSize) // 线性查找, O(N)
    {
        if(k == arr[i].key)
            return arr[i].value;
        i++;
    }
    return Value();
}

#endif