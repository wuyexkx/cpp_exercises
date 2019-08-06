#include <iostream>
#include "sequenceQueue.h"
using namespace std;

// FIFO LILO 顺序队列--环形队列,利用删除后的空间
int main()
{
    seqQueue<char> q(4);
    q.Push('A');
    cout << q.Front() << "  " << q.Rear() << endl;
    q.Push('B');
    cout << q.Front() << "  " << q.Rear() << endl;
    q.Push('C');
    cout << q.Front() << "  " << q.Rear() << endl;
    q.Pop();
    cout << q.Front() << "  " << q.Rear() << endl;
    q.Push('D');
    cout << q.Front() << "  " << q.Rear() << endl;
    q.Push('E');
    cout << q.Front() << "  " << q.Rear() << endl;

    return 0;
}
