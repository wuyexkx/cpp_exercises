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
    A():i(0){cout << "A::A()" <<endl;}; //�ڹ��캯���г�ʼ����Ա����
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
//    a[0] = 'a'; //aָ��Ŀռ�Ϊconst�ռ䣬�ڴ������ɶ�����д
//    cout << a << endl;

    const B b;
    b.f();

//    int b = 10;
//    f(&b);

    return 0;
}
