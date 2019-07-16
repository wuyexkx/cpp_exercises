#include <iostream>

using namespace std;


class A
{
private:
    int private_num = 10;
public:
    A(int num);
    A(const A &a);
    ~A();
    void show();
};
A::A(int num){cout << "constructor" << endl; private_num = num;}
A::A(const A &a){cout << "copyConstructor" << private_num << endl;}
A::~A(){cout << "deconstructor" << endl;}
void A::show(){cout << "private_num" << private_num << endl;}


int main()
{
    A a(10);
    a.show();
}
