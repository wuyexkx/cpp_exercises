
// 数据对应的hash值 % 容器大小  （hash值对size[53]取余），很可能造成碰撞，于是采用Separate Chaining方法
//  将发生碰撞的值连接到同一个地方，串接起来。 但是也可能同一个地方串接很长，
//  影响查找效率(经验值长度>=size时)，于是打散串接、扩大size，重新计算应该的位置（rehash）。所以哈希表也叫散列表
//      其中扩大容量的方法是，扩增两倍size查找2xsize附近的质数作为新的size。所以bucket个数永远>链数（某个bucket的size）
// 

// hashtable底层
template<class Value, class Key, class HashFcn, // 
         class ExtractKey, class EqualKey, 
         class Alloc=alloc>



