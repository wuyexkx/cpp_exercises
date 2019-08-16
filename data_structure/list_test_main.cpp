#include <iostream>
#include "list_test.h"


int main()
{
    List<int> l; 
    l.Insert(0);
    l.Insert(1);
    l.Insert(2);
    l.Insert(3);
    l.Insert(4);

    l.showList();

    l.Invert();
    l.showList();
    
    return 0;
}
