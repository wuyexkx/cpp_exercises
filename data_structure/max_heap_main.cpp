#include <iostream>
#include "max_heap.h"

using namespace std;

int main()
{
    maxHeap<int> heap(30);
    heap.Push(10); 
    heap.Push(5);    // cout << heap.Top() << endl;
    heap.Push(21);   // cout << heap.Top() << endl;
    heap.Push(55);
    heap.Push(7);
    heap.show();

    heap.Pop();  heap.show();
    heap.Pop();  heap.show();
    heap.Pop();  heap.show();
    heap.Pop();  heap.show();
    heap.Pop();   

    // 用堆来 排序
    maxHeap<int> heap1(100);
    int a[10] = {2, 33, 44, 1, 3, 12, 54, -5, 22, 0};
    for(int i = 0; i < 10; i++) heap1.Push(a[i]); // 压入堆  
    for(int i = 0; i < 10; i++) 
    {
        a[i] = heap1.Top(); // 取出
        heap1.Pop();        // 删除
    }
    for(int i = 0; i < 10; i++) cout << a[i] << " ";
    cout << endl;

/* output:
    --------------------------
    55 21 10 5 7 nums:5
    --------------------------
    --------------------------
    21 7 10 5 nums:4
    --------------------------
    --------------------------
    10 7 5 nums:3
    --------------------------
    --------------------------
    7 5 nums:2
    --------------------------
    --------------------------
    5 nums:1
    --------------------------
    54 44 33 22 12 3 2 1 0 -5 
*/
    return 0;
}
