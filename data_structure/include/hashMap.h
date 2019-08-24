#ifndef __HASH_MAP_H
#define __HASH_MAP_H

#include <vector>
#include <string>

template<class Key, class Value>
class HashMap
{
public:
    HashMap(const int size = 10)
    : arr(size), crtSize(0) { }
    void Put(const Key& k, const Value& v);
    Value Get(const Key& k);
    unsigned int hash(const Key& k) const // 计算字符串的hash值 (计算出一个数字 使之唯一代表字符串)
    {
        unsigned hashVal = 0;
        for(size_t i=0; i<k.length(); ++i)
            hashVal = hashVal << 7^k[i];  // 每个字符都参与计算      
        hashVal &= 0x7FFFFFFF;

        return hashVal % arr.size();      // 限定到 0~size之间
    }
private:
    struct Data // (key, value), vector存放的类型就算Data
    {
        Data(const Key& k = Key(), const Value& v = Value()) // 默认初值T()
        : key(k), value(v) { }
        Key key;
        Value value;
    };
    std::vector<Data> arr;
    int crtSize;
};
template<class Key, class Value>
void HashMap<Key, Value>::Put(const Key& k, const Value& v)
{
    if(crtSize == arr.size())
    {
        std::cerr << "map has fulled.\n";
        return; // 超过了
    } 
    arr[hash(k)] = Data(k, v);
    crtSize++;
}
template<class Key, class Value>
Value HashMap<Key, Value>::Get(const Key& k) 
{
    unsigned int h = hash(k);
    if(arr[h].key == k)  // 通过计算k的hash 查找到的key 和 给定的k 相等才返回正确值
        return arr[h].value;
    return Value();
}


#endif