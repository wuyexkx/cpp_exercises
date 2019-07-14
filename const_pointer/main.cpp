#include <iostream>

using namespace std;

void f(const int* x);
void f(const int* x){
//    (*x)++;
    cout << *x << endl;
}


class A {
private:
    int i;
public:
    A():i(0){cout << "A::A()" <<endl;}; //在构造函数中初始化成员变量
    void ff() const;
};
void A::ff() const {
//    i++; //error: increment of member 'A::i' in read-only object|
    cout << i << endl;
}


class B {
private:
	int i;
public:
    B():i(0) {}
	void f() {cout << "f()" << endl;}
	void f() const {cout << "f const" << endl;}
};



int main()
{
//    char *a = "hello world!";
//    a[0] = 'a'; //a指向的空间为const空间，在代码段里，可读不可写
//    cout << a << endl;

    const B b;
    b.f();

//    int b = 10;
//    f(&b);

    return 0;
}
