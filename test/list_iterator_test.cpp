#include <iostream>
#include <string>
#include "list_iterator_test.h"

using namespace std;

int main()
{
    List<int> l;
    l.push_front(0);
    l.push_front(1);
    l.push_front(2);
    l.push_front(3);
    l.print();

    for(auto it=l.begin(); it!=l.end(); it++) // i++
        cout << *it << " ";
    cout << endl;

    for(auto it=l.begin(); it!=l.end(); ++it) // ++i
        cout << *it << " ";
    cout << endl;

    return 0;
}
