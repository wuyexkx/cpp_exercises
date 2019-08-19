// 用数组做 循环队列 ,内存扩大两倍,,平均填充度75%, 空闲25%
#include <iostream>
#include "listQueue.h"

using namespace std;

int main()
{

listQueue<int> lq;
lq.enqueue(10);
cout << lq.getFront() << endl;
cout << lq.getBack() << endl;
cout << "-----------------------\n";
lq.enqueue(11);
cout << lq.getFront() << endl;
cout << lq.getBack() << endl;
cout << "-----------------------\n";
lq.enqueue(12);
cout << lq.getFront() << endl;
cout << lq.getBack() << endl;

cout << "-----------------------\n";
// while(!lq.IsEmpty()) // 循环取出队首
 cout << lq.dequeue() << endl;
 cout << lq.dequeue() << endl;
 cout << lq.dequeue() << endl;
 cout << lq.dequeue() << endl; // 取完了还在取

return 0;
}