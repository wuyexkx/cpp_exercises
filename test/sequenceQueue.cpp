#include <iostream>
#include "sequenceQueue.h"
using namespace std;

int main()
{

    seqQueue<int> sq(2);
    cout << "capacity: " << sq.Capacity() << endl;
    sq.Push(0);
    sq.Push(1);
    sq.Push(2);
    sq.Push(3);
    sq.Push(4);
    sq.Push(5);
    sq.Push(6);
    cout << "capacity: " << sq.Capacity() << endl;

    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();
    cout << "front: " << sq.Front() << endl;
    sq.Pop();

    return 0;
}