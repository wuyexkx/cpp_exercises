#include <iostream>

using namespace std;

int main()
{
    int i;
    int&j = i;
    j = 10;//i���ű�Ϊ10
    cout << j << endl;
    return 0;
}
