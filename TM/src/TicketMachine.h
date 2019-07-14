//
// Created by wyxkx on 2019/4/24.
//

#ifndef TICKETMACHINE_TICKETMACHINE_H
#define TICKETMACHINE_TICKETMACHINE_H


class TicketMachine {
public:
    void insertMoney(int money);
    void decraseMoney(int money);
    void showBalance();
    int *  pointer_Private_balance();
    int & reference_Private_balance();
private:
    int balance = 100;
};


#endif //TICKETMACHINE_TICKETMACHINE_H
