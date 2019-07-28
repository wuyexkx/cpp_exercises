#include "clsWithoutPointerMember.h"

using namespace std;


void complex::show_complex(string name)
{
    cout << name << ": (" << this->re << " " << this->im << "i)\n";
}


