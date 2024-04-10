#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "account_ParthKharkar.h"
#include "stockaccount_ParthKharkar.h"
#include "bankaccount_ParthKharkar.h"

using namespace std;

account acc;
stockaccount stk;
bankaccount bk;

int c1, c2;

void stocks()
{
    c1 = 0;
    cout << "OPTION 1: DISPLAY THE PRICE FOR A STOCK SYMBOL " << endl;
    cout << "OPTION 2: DISPLAY THE CURRENT PORTFOLIO " << endl;
    cout << "OPTION 3: BUY SHARES " << endl;
    cout << "OPTION 4: SELL SHARES " << endl;
    cout << "OPTION 5: VIEW A GRAPH FOR THE PORTFOLIO VALUE " << endl;
    cout << "OPTION 6: VIEW TRANSACTION HISTORY " << endl;
    cout << "OPTION 7: RETURN TO CURRENT MENU\n" << endl;
    cin >> c1;
    if(c1 < 7)
        {  
            cin.clear();
        }
}
void bank()
{
    c2 = 0;
    cout << "OPTION 1: VIEW ACCOUNT BALANCE " << endl;
    cout << "OPTION 2: DEPOSIT MONEY " << endl;
    cout << "OPTION 3: WITHDRAW MONEY " << endl;
    cout << "OPTION 4: PRINT OUT HISTORY\n " << endl;  
    cin >> c2;
    if(c2 > 4)
        {  
            cin.clear();
        } 
}
int main()
{
    char c;
    int choice = 0;
    do
    {
        cout << "\nWELCOME TO THE ACCOUNT MANAGEMENT SYSTEM!" << endl;
        cout << "OPTION 1: STOCK ACCOUNT" << endl;
        cout << "OPTION 2: BANK ACCOUNT" << endl;
        cout << "OPTION 3: EXIT \n" << endl;
        cout << "ENTER THE CHOICE NUMBER TO BE EXECUTED!" << endl;
        cin >> choice;
        if(choice > 3)
        {   
            cin.clear();
        }
        else
        {
            switch(choice)
            {
                case 1: stocks();
                        switch(c1)
                        {
                            case 1: cout << "Printing Price of Latest Stock -" << endl;
                                    stk.price_of_stock();
                                    break;

                            case 2: cout << "Printing Portfolio: " << endl;
                                    stk.print_display_portfolio();
                                    break;

                            case 3: cout << "Performing Purchase of Shares of Latest Stock -" << endl;
                                    stk.buy_share();
                                    break;

                            case 4: cout << "Performing Sale of Shares of Latest Stock -" << endl;
                                    stk.sell_share();
                                    break;

                            case 5: cout << "Graphing Portfolio of the Latest Stock -" << endl;
                                    stk.graph_portfolio_value( );

                            case 6: cout << "Printing Total Transaction History -" << endl;
                                    stk.transaction_history();
                                    break;

                            case 7: 
                            
                            default: break;
                        }
                        break;

                case 2: bank(); 
                        switch(c2)
                        {
                            case 1: cout << "Printing Account Statement -" << endl;
                                    bk.view_acc_balance();
                                    break;

                            case 2: cout << "Performing Deposit Operation -" << endl;
                                    bk.deposit_money();
                                    break;
                        
                            case 3: cout << "Performing Withdrawal Operation -" << endl;
                                    bk.withdraw_money();
                                    break;

                            case 4: cout << "Printing Total Transaction History -" << endl;
                                    bk.print_history();
                                    break;
                            
                            default: break;

                        }
                        // return 0;
                        break;

                case 3: cout << "WOULD YOU LIKE TO EXIT THE PROGRAM?\nTYPE Y FOR YES, N FOR NO" << endl;
                        cin >> c;
                        if (c == 'Y' || c == 'N')
                            exit(0);
                        // return 0;

                default: break;                             
            }
        }      
    } while (choice!=0);   
}