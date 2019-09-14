#include <iostream>
#include "single_list.h"
using namespace std;

int main()
{
    List<int> l;
    cout <<l.isEmpty() << endl;
    l.Push_front(10);
    l.Push_front(11);
    cout <<l.isEmpty() << endl;

    return 0;
}