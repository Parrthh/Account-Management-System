#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <iostream>
#include <string>

#include "account_ParthKharkar.h"

using namespace std;

class bankaccount : public account
{
    public:
        double balance;
        double money;
        string file_transactions;
        bankaccount();
        ~bankaccount();
        void set_balance();
        void view_acc_balance();
        void deposit_money();
        void withdraw_money();
        void print_history() const;
        void transaction_list(string occurent, double money);
};

#endif