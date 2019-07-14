#include <iostream>

//��������private friend
using namespace std;
class A{
private:
    int i;
    int *p;
public:
    A(){cout << endl << "A::A()";}
    ~A(){cout << endl << "A::~A()";}
    void haha(int ii){i = ii;} //�޸�˽�б���
    void f(A *a){cout << endl << "A::f(A *a) a -> i = " << a->i;} //���˽�б���
};


// friendʹ�ã����������ʱ��Ȩ
// Ҳ���ڱ���ʱ�̼��
struct X;//ǰ������
struct Y{
    void f(X*);
};
struct X{ //����
private:
    int i; //X��˽�г�Ա
public:
    void initialize();
    friend void g(X*, int);
    friend void Y::f(X*);
    friend struct Z;
    friend void h();
};
void X::initialize(){
    i = 0;
}
void g(X* x, int j){
    x->i = j;
}
void Y::f(X* x){
    x->i = 47;
}
struct Z{
private:
    int k;
};


int main(){
    A *p = new A[10]; //����һ�����A���͵ĵ����飬������ָ�븳ֵ��p
    A a; //����a����
    a.haha(88); //����a��haha��������a˽�����Ե�ֵ
    p[0].f(&a); //p�����0��Ԫ����һ��A���󣬵��ö����f����������A���Ͷ���a��ָ��
    //���88��private���������˵�ģ�ͬ��Ķ���֮������໥����˽�����ԣ�˽�г�Ա������
    //private������ֻ�ڱ���ʱ�̣�����ʱ��ȫ�޹أ�����������Դ����.cpp�г���
    delete[] p;
    return 0;
}
