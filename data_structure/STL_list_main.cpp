#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<int> listIntegers;
    listIntegers.push_front(0);
    listIntegers.push_front(1);
    listIntegers.push_front(2);
    listIntegers.push_front(3);
    
    list<int>::iterator i = listIntegers.begin();
    while(i != listIntegers.end())
    {
        cout << *i;
        i++;
        if(i != listIntegers.end()) cout << " -> ";
    }

return 0;
}

