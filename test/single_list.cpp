#include <iostream>
#include "single_list.h"
using namespace std;

int main()
{
    List<int> l;
    l.Push_front(10);
    l.Push_front(11);
    l.Push_front(12);
    l.Push_front(13);
    l.print();

    l.Delete(10);
    l.print();
    l.Pop_front();
    l.Delete(12);
    l.print();
    l.Pop_front();
    l.print();

    l.Push_front(10);
    l.Push_front(11);
    l.Push_front(12);
    l.Push_front(13);
    l.print();
    l.Invert();
    l.print();

    auto it = l.begin();
    ++it;

    // output:
        // 13->12->11->10
        // 13->12->11
        // 11
        // empty!
        // 13->12->11->10
        // 10->11->12->13
    return 0;
}
