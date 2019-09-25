
// 分配器大多用在容器中，效率直接影响容器的效率
//  c++所有的分配动作最后都是调用operator new()完成（由crt[c runtime lib]提供），然后交给操作系统
// operator new() 和 malloc()
//  实际分配的内存比申请的大（cookie夹心饼干）

