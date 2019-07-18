#include <iostream>
#include "operator_overloading.h"

using namespace std;


int main()
{
    complex p1(2, 1);
    p1.show_complex("p1");
    complex p2(1, 1);
    p2.show_complex("p2");

    complex p3 = p1 + 1;
    p3.show_complex("p3");
    complex p4 = 1 + p1;
    p4.show_complex("p4");

    p3 = +p4;
    p3.show_complex("p3");

    cout << (p3 == p4) << endl;
    complex p5(1);
    cout << (p5 == 1) << endl;
    cout << (2 == p5) << endl;

    cout << p4 << p1;

    return 0;
}
