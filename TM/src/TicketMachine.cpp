
#include "TicketMachine.h"
#include <iostream>
using namespace std;

//::解析符，说明用类里面的方法，而不是全局的
// 通过公共函数为私有成员赋值
void TicketMachine::decraseMoney(int money)
{
    balance -= money;
}

void TicketMachine::insertMoney(int money)
{
    balance += money;
}

void TicketMachine::showBalance()
{
    cout << "Current balance: " << balance << endl;
}

// 公共函数 返回 私有变量的 指针
int *  TicketMachine::pointer_Private_balance()
{
    return &balance;
}
// 公共函数 返回 私有变量的 引用
int & TicketMachine::reference_Private_balance()
{
    return balance;
}