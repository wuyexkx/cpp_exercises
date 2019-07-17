#include <iostream>
#include "operator_overloading.h"

using namespace std;


int main()
{
    complex p1(2, 1);

    cout << "p1.real: " << p1.real() << endl;
    cout << "p1.imag: " << p1.imag() << endl;

    complex p2(1, 1);
    complex p3(3, 3);

    cout << "p2.real: " << p2.real() << endl;
    cout << "p2.imag: " << p2.imag() << endl;

    p1 += p2 += p3;

    cout << "p11.real: " << p1.real() << endl;
    cout << "p11.imag: " << p1.imag() << endl;

    cout << "p22.real: " << p2.real() << endl;
    cout << "p22.imag: " << p2.imag() << endl;


    return 0;
}
