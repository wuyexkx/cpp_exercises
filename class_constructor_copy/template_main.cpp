#include "template.h"

int main()
{
    // 类模板，使用时需要指定typename
    complex<double> c1(2.5, 3.5);
    complex<int> c2(3, 2);
    complex<int> c3(3, 4);

    c2 += c3;
    cout << "real: " << c2.real() << endl;
    cout << "imag: " << c2.imag() << endl;


    // 函数模板
    stone s1(1,1,2), s2(2,2,5), s3;
    cout << "s3.get_weight: " << s3.get_weight() << endl;
    // 使用时，编译器会对 函数模板 进行 参数推导(argument deduction)
    // 参数推导结果T为stone，于是调用stone::operator<
    s3 = mini(s1, s2);
    cout << "s3.get_weight: " << s3.get_weight() << endl;

    return 0;
}


