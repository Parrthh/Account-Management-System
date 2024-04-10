#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <filesystem>

#include "bankaccount_ParthKharkar.h"

using namespace std;

bankaccount :: bankaccount()
{
    this->set_balance();
}

bankaccount :: ~bankaccount()
{
    std::fstream balance_file;
    balance_file.open("cash_balance.txt", std::fstream::out);
    balance_file << balance;
    balance_file.close();
}

void bankaccount :: set_balance()
{
    std::fstream Balance;
    Balance.open("Balance.txt", std::fstream::in);
    if(!Balance) 
    {
        Balance.open("Balance.txt", std::fstream::in);
        balance = 10000;
        Balance << balance;
        Balance.close();
    }
    else
    {
        Balance >> balance;
        Balance.close();
    }
    return;
}

void bankaccount :: view_acc_balance()
{
    ifstream acc_bank("Transaction_History.txt");
    acc_bank >> balance;

    cout << "Total Amount Available in Your Bank Account: \n" << balance;

    return;
}

void bankaccount :: deposit_money()
{
    double bank_deposit;
    cout << "Enter the Amount You Would Like to Deposit in Your Account: " << endl;
    cin >> money;

    ifstream bank("balance_history.txt");
    bank >> balance;

    bank_deposit = balance + money;

    ofstream bank_data;
    bank_data.open("balance_history.txt");
    bank_data << bank_deposit;
    if(money <= 25000)
    {
        cout << "Total Amount Available in Your Bank Account: " << (bank_deposit);
        transaction_list("MONEY_DEPOSITED", money);
    }
    else 
    {
        cout << "Amount Exceeds $25000. Please Do Multiple Transactions or Try Again the Next Day" << endl;
    }
}

void bankaccount :: withdraw_money()
{   
    double bank_withdraw;
    cout << "Enter the Amount You Would Like to Withdraw From Your Account: " << endl;
    cin >> money;

    ifstream bank_with("balance_history.txt");
    bank_with >> balance;

    bank_withdraw = balance - money;

    ofstream bank_withdrawdata;
    bank_withdrawdata.open("balance_history.txt");
    if (balance < money)
    {
        cout << "Transaction Failed due to Insufficient Funds" << endl;
    }
    else if (money <= 10000)
    {
        cout << "Total Amount Available in Your Bank Account: " << bank_withdraw;
    }
    else 
    {
        cout << "Amount Exceeds $10000. Please Do Multiple Transactions or Try Again the Next Day" << endl;
    }
    transaction_list("MONEY_WITHDRAWN", money);
}


 void Printbanktable(string line)
        {
            string k = "";
            for (auto x : line)
            {
                if (x == ' ')
                {
                    if (k == "Fri")
                    {
                        cout<<k;
                    }
                    else{
                    cout << k << setw(30);
                    }
                    k = "";
                }
                else {
                    k = k + x;
                }
            }
            cout << k << endl;
        }


void bankaccount :: print_history() const
{
    string bank_hist;

    ifstream read_data("Transaction_History.txt");
    cout << "EVENT" << setw(35) <<"Amount" << setw(35)<< "Date" <<setw(35) << "Balance\n";
    while (getline (read_data, bank_hist)) 
    {
        Printbanktable(bank_hist);
    }
}

void bankaccount :: transaction_list(string event, double money)
{
    char date[11];
    time_t transcation_seconds;
    transcation_seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&transcation_seconds);
    strftime(date, 11, "%m/%d/20%y", timeinfo);

    ofstream bank_transaction;
    bank_transaction.open("Transaction_History.txt" , ios::app);
    bank_transaction << event <<" "<< money<<" "<< date <<" "<< balance <<"\n";
    bank_transaction.close();


    return;
}


