#include <iostream>
#include "TicketMachine.h"

using namespace std;

// 获取私有变量的手段
// 指针和引用都可以 通过公共函数 在类的外部 修改私有变量
int main()
{
    TicketMachine TM;
    cout << "\ninit balance = ";
    TM.showBalance();

    cout << "\ninert 10 = " ;
    TM.insertMoney(10);
    TM.showBalance();

    cout << "\ndecrase 5 = ";
    TM.decraseMoney(5);
    TM.showBalance();

    cout << "\npointer add 100 = ";
    int *b = TM.pointer_Private_balance();
    *b += 100;
    TM.showBalance();

    cout << "\nreference sub 50 = ";
    int &r = TM.reference_Private_balance();
    r -= 50;
    TM.showBalance();
    return 0;
}
