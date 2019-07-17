#include <iostream>
#include "operator_overloading.h"

using namespace std;


int main()
{
    complex p1(2, 1);
    complex p2(1, 1);
    p1 += p2;

    cout << "p1: " << p1.real() << endl;
    cout << "p1: " << p1.imag() << endl;


    return 0;
}
