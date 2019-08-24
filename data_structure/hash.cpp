#include <iostream>
#include <string>
#include <map> // 映射(字典) 二叉树(红黑树)映射, 不是hash映射
#include <unordered_map> // hash映射
#include "linearMap.h"   // 简单map小试验,线性
#include "hashMap.h"

using namespace std;

// hash数据结构, 可做hash集 也可做hash映射  (hash也叫散列), 无法排序
// 所有数据结构中 hash结构速度最快.
// O(N^2) 冒泡
// O(N) 线性查找
// O(logN) 二叉树(二分查找的速度)
// O(1) hash

int main()
{
    // 库里的map
    cout << "----使用库里的map(二叉树)-----\n";
    map<string, int> m; // 二叉树映射
    m["a"] = 100;
    cout << m["a"] << endl;

    cout << "----使用库里的map(hash)-----\n";
    unordered_map<string, int> umap; // hash映射
    umap["aa"] = 12;
    cout << umap["aa"] << endl;

    // 自己写的线性map
    cout << "-----自写的map(线性)-----\n";
    LinearMap<string, int> lm;
    lm.Put("aa", 100);
    lm.Put("bb", 101);
    lm.Put("cc", 102);
    cout << lm.Get("bb") << endl;

    // 自写的hash map
    cout << "-----自写的hash map-----\n";
    HashMap<string, int> hm;
    hm.Put("aa", 100);
    hm.Put("bb", 101);
    hm.Put("cc", 102);
    hm.Put("dd", 103);
    hm.Put("ee", 104);
    hm.Put("ff", 105);
    hm.Put("gg", 106);
    hm.Put("hh", 107);
    hm.Put("ii", 108);
    hm.Put("jj", 109);
    cout << hm.Get("aa") << endl;
    cout << hm.Get("bb") << endl;
    cout << hm.Get("cc") << endl;
    cout << hm.Get("dd") << endl;
    cout << hm.Get("ee") << endl;
    cout << hm.Get("ff") << endl;
    cout << hm.Get("gg") << endl;
    cout << hm.Get("hh") << endl;
    cout << hm.Get("ii") << endl;
    cout << hm.Get("jj") << endl;

  /* output:
        ----使用库里的map(二叉树)-----
        100
        ----使用库里的map(hash)-----
        12
        -----自写的map(线性)-----
        101
        -----自写的hash map-----
        100
        101
        102
        103
        104
        105
        106
        107
        108
        109
  */
    return 0;
}

