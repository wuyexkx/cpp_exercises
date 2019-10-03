#include <iostream>
#include "list_stack.h"
using namespace std;

int main()
{
    list_stack<int> ls;
    ls.push(0);
    cout << ls.Top() << endl;
    ls.push(1);
    ls.push(2);
    ls.push(3);
    cout << ls.Top() << endl;

    ls.pop();
    cout << ls.Top() << endl;
    ls.pop();
    cout << ls.Top() << endl;    
    ls.pop();
    cout << ls.Top() << endl;    
    ls.pop();
    cout << ls.Top() << endl;

    return 0;
}

