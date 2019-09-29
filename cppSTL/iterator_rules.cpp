
// 迭代器是 连接 算法和容器 的桥梁
// 所以设计迭代器需要满足一些要求才行   // 算法rotate算法为例


// 其中包含5大项， 但是后两项从未使用
// 1. category 分类，指移动性质，有的it只能向前，有的可以往回走，有的可以+=8等等（算法会通过萃取机取出it的分类性质）
// 2. distance 距离，两个迭代器之间的距离，用什么类型表示
// 3. value type 迭代器所指的数据类型
// 4. reference
// 5. pointer

// 算法不能直接问iterator，因为iterator可能不是class （图片 萃取机2.jpg）
// 指针也是一种iterator，退化的iterator，但并不是class
// 用萃取机得到这个iterator是class还是pointer（萃取机，类似中介层，多加一个接口） 
//  间接问iterator的value_type, 先问traits it的value_type是什么，剩下的交给traits
//      traits内部用特化来区别class，用偏特化区别pointer（T* or const T*）
