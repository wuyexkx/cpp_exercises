#include <iostream>
using namespace std;

// nullptr的意思告诉编译器传递的是 空指针
void f(int) { cout << "f(int)\n"; }
void f(void*) { cout << "f(void*)\n"; }

int main()
{
    f(0);       // f(int)
    f(nullptr); // f(void*)

    return 0;
}