#include <iostream>
#include "sequenceStack.h"
using namespace std;


int main()
{
    seqStack<int> seqarr(3);

    for(int i=0; i<4; i++) seqarr.Push(i);
    seqarr.print();
    cout << "current size: " << seqarr.getSize() << endl;
    cout << seqarr.Top() << endl;
    seqarr.Pop();
    cout << seqarr.Top() << endl;
    seqarr.Pop();
    cout << seqarr.Top() << endl;    
    seqarr.Pop();
    cout << seqarr.Top() << endl;
    seqarr.Pop();
    cout << seqarr.Top() << endl;
    
    return 0;
}