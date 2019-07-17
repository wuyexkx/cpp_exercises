#include <iostream>
#include "operator_overloading.h"

using namespace std;


int main()
{
    complex p1(2, 1);

    cout << "p1.real: " << p1.real() << endl;
    cout << "p1.imag: " << p1.imag() << endl;

    complex p2(1, 1);
    complex p3 = p1 + 1;
    complex p4 = 1 + p1;

    cout << "p3.real: " << p3.real() << endl;
    cout << "p3.imag: " << p3.imag() << endl;
    cout << "p4.real: " << p4.real() << endl;
    cout << "p4.imag: " << p4.imag() << endl;

    return 0;
}
