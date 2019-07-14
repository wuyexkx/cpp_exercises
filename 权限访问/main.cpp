#include <iostream>

//访问限制private friend
using namespace std;
class A{
private:
    int i;
    int *p;
public:
    A(){cout << endl << "A::A()";}
    ~A(){cout << endl << "A::~A()";}
    void haha(int ii){i = ii;} //修改私有变量
    void f(A *a){cout << endl << "A::f(A *a) a -> i = " << a->i;} //输出私有变量
};


// friend使用，运算符重载时授权
// 也是在编译时刻检查
struct X;//前向声明
struct Y{
    void f(X*);
};
struct X{ //定义
private:
    int i; //X的私有成员
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
    A *p = new A[10]; //开辟一个存放A类型的的数组，并返回指针赋值给p
    A a; //创建a对象
    a.haha(88); //调用a的haha方法设置a私有属性的值
    p[0].f(&a); //p数组第0个元素是一个A对象，调用对象的f方法，传入A类型对象a的指针
    //输出88，private相对于类来说的，同类的对象之间可以相互访问私有属性（私有成员变量）
    //private的限制只在编译时刻，运行时完全无关，面向对象仅在源代码.cpp中成立
    delete[] p;
    return 0;
}
