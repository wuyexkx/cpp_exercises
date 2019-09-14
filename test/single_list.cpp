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
    
    return 0;
}