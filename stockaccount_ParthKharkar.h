#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

#include "account_ParthKharkar.h"

using namespace std;

class Node
{
    public:
        Node *next_stock;
        Node *previous_stock;
        string stock_symbol;
        double stock_volume;
        double stock_price;
        double stock_total_valuation;
        string stock_time;

    Node(string sym , double vol ,double st_price, string st_time):stock_symbol(sym), stock_volume(vol), stock_price(st_price), stock_time(st_time)
    {
        next_stock = NULL;
        previous_stock = NULL;
        stock_total_valuation = stock_price*stock_volume;
    }
};

class stockaccount : public account
{
    public:
        Node * head;
        Node * tail;

        stockaccount()
        {
            head = NULL;
            tail = NULL;
        }

        void toInsert(string stock_symbol, double stock_volume, double stock_price, string stock_time)
        {
            Node * temp = new Node(stock_symbol, stock_volume, stock_price, stock_time);
            if(head == NULL && tail == NULL)
            {
                head = temp;
                tail = temp;
                
                cout << head->stock_symbol;
            }
            else if(head == tail)
            {
                if (head->stock_symbol == temp->stock_symbol)
                {
                    head->stock_volume = head->stock_volume + temp->stock_volume;
                    
                }
                else
                {
                    if (temp->stock_total_valuation > head->stock_total_valuation)
                    {
                        head = temp;
                        head->next_stock = tail;
                        tail->previous_stock = head;
                        
                    }
                    else
                    {
                        head->next_stock = temp;
                        temp->previous_stock = head;
                        tail = temp;
                        

                    }
                }

            }
            else
            {
                Node * ptr1;
                ptr1 = head;
                int flag1 = 0;
                while (ptr1 != NULL)
                {
                    if(ptr1->stock_symbol == temp->stock_symbol)
                    {
                        flag1 = 1;
                        
                        break;
                    }
                    else
                    {
                        ptr1 = ptr1->next_stock;
                    }
                    
                }
                if (flag1 == 1)
                {
                    ptr1->stock_volume = ptr1->stock_volume + temp->stock_volume;
                    
                }
                else
                {
                    
                
                    if(temp->stock_total_valuation >= head->stock_total_valuation)
                    {
                        Node * current;
                        current = head;
                        temp->next_stock = current;
                        current->previous_stock = temp;
                        head = temp;
                        
                    }
                    else if(temp->stock_total_valuation <= tail->stock_total_valuation)
                    {
                        Node * current;
                        current = tail;
                        temp->previous_stock = current;
                        current->next_stock = temp;

                        tail = temp;
                        

                    }
                    else
                    {
                        Node * itr1;
                        itr1 = head;
                        while(temp->stock_total_valuation <= itr1->stock_total_valuation)
                        {
                            itr1 = itr1->next_stock;
                        }

                        Node * itr2;
                        itr2 = itr1->previous_stock;
                        itr2->next_stock = temp;
                        temp->previous_stock = itr2;
                        temp->next_stock = itr1;
                        itr1->previous_stock = temp;
                        
                    }
                }
            }
        }

        void print_display_portfolio()
        {
            Node * current_node;
            double tval = 0;
            
            current_node = head;
            cout<<"\nComSym\tNum\tPrice\tTotalValue\n";
            cout << "\n------------------------------ \n";
            while (current_node != NULL)
            {   
                tval=tval + current_node->stock_total_valuation;

                cout << current_node->stock_symbol<<"\t" << current_node->stock_volume <<"\t" << current_node->stock_price << "\t" << current_node->stock_total_valuation << endl;
                current_node = current_node->next_stock;

            }   
            cout << "Total valuation: \n" << tval;
        }

        double updatelist(string stock_symbol, double stock_volume, string stock_time, double stock_price)
        {   
            Node * temp;
            int flag = 0;
            temp = head;
            
            while(temp!= NULL)
            {
                if (temp->stock_symbol == stock_symbol)
                {
                    flag = 1;
                    break;
                }
                else
                {
                    temp = temp->next_stock;
                }
            }
            if (flag == 1)
            {
                cout << temp->stock_symbol;
                
            
            

                if (temp->stock_volume >= stock_volume)
                {
                    if (temp == head)
                    {
                        head = head->next_stock;
                        temp->next_stock = NULL;
                        head->previous_stock = NULL;
                        temp->stock_volume = temp->stock_volume - stock_volume;
                        temp->stock_total_valuation = temp->stock_price * temp->stock_volume;
                        
                        toInsert(temp->stock_symbol, temp->stock_volume, temp->stock_price, temp->stock_time);
                        return stock_volume * temp->stock_price;
                    }
                    else if (temp == tail)
                    {
                        tail = tail->previous_stock;
                        temp->previous_stock = NULL;
                        tail->next_stock = NULL;
                        temp->stock_volume = temp->stock_volume - stock_volume;
                        temp->stock_total_valuation = temp->stock_price * temp->stock_volume;
                        toInsert(temp->stock_symbol, temp->stock_volume, temp->stock_price, temp->stock_time);
                        return stock_volume * stock_price;
                    }
                    else
                    {
                        Node * temp1;
                        Node * temp2;
                        temp1 = temp->previous_stock;
                        temp2 = temp->next_stock;
                        temp1->next_stock = temp2;
                        temp2->previous_stock = temp1;
                        temp->next_stock = NULL;
                        temp->previous_stock = NULL;
                        temp->stock_volume = temp->stock_volume - stock_volume;
                        temp->stock_total_valuation = stock_price * temp->stock_volume;
                        toInsert(temp->stock_symbol, temp->stock_volume, stock_price, temp->stock_time);
                        return stock_volume * stock_price;
                    }
                }
                else
                {
                    cout << "ERROR! NO ENOUGH VOLUME";
                    return 0;
                }
            }
            else
            {
                cout << "SHARE NOT FOUND!";
                return 0;
            }
        }

        void price_of_stock()
        {
            string company_symbol;
            int file_check = 0;
            cout << "PLEASE ENTER THE COMPANY SYMBOL YOU WANT TO CHECK THE PRICE FOR:";
            cin >> company_symbol;
            ifstream data;
            double stock_price;

            string stock_symbol;
            string stock_time;

            int read_file = rand() % 2;
            if (read_file == 0)
            {
                data.open("Result_1.txt");
            }
            if (read_file == 1)
            {
                data.open("Result_2.txt");
            }
            while(!data.eof()) {
                string word;
                data >> word;
                
                if (word == company_symbol) {
                    data >> stock_price;
                    cout << "\n COMPANY SYMBOL PRICE PER SHARE \n";
                    cout << setw(8) << stock_symbol << setw(10) << stock_price;
                    file_check = 1;
                }
            }
            data.close();
            if (file_check == 0)
            {
                cout << "THE SYMBOL CANNOT BE FOUND!";
            }
            cout << endl;

        }


        void buy_share()
        {
            char event = '3';
            string company_symbol;
            string stock_symbol;
            string stock_time;
            double stock_price;
            double stock_volume = 0;
            double maximum_volume = 0;
            double maximum_amount;
            double total_valuation;
            double stock_total_valuation;
            char choice;
            int file_check = 0;
            double balance = 0;


            ifstream cash_file("balance_history.txt");
            if (cash_file.is_open() == false)
            {
                
                balance = 10000;
            }
            else
            {
                cash_file >> balance;
            }


            cout << "PLEASE ENTER THE COMPANY SYMBOL YOU WISH TO PURCHASE THE SHARE FOR: " << endl;
            cin >> company_symbol;
            ifstream data;
            int read_file = rand() % 2;
            if (read_file == 0)
            {
                data.open("Result_1.txt");
            }
            if (read_file == 1)
            {
                data.open("Result_2.txt");
            }

            for (int stock_list = 0; stock_list < 50; stock_list++)
            {
                data >> stock_symbol >> stock_price >> stock_time;
                if (company_symbol == stock_symbol)
                {
                    cout << "ENTER THE NUMBER OF SHARES YOU WISH TO PURCHASE FOR THE COMPANY: ";
                    cin >> stock_volume;

                    stock_total_valuation = stock_price * stock_volume;
                    if (stock_total_valuation > balance)
                    {
                        cout << stock_total_valuation;
                        cout << balance;
                        cout << "THE AMOUNT IN THE ACCOUNT IS LESS.\n HENEC, TRANSACTION FAILED!";
                    }

                    else
                    {
                        cout << "ENTER THE MAXIMUM AMOUNT WILLING TO PAY: ";
                        cin >> maximum_amount;

                        if(stock_total_valuation > maximum_amount)
                        {
                            cout << maximum_amount;
                            cout << "STOCK VALUATION!";
                            cout << stock_total_valuation;

                            cout << "THE AMOUNT IN THE ACCOUNT IS LESS THAN THE TOTAL TRANSACTION. HENCE, TRANSACTION FAILED!";

                        }
                        else
                        {
                            cout << balance << "\n";

                            balance -= stock_price * stock_volume;
                            cout << balance << "\n";
                            ofstream balance_history;
                            balance_history.open("balance_history.txt");

                            balance_history << balance;

                            cout << "YOU HAVE PURCHASED SHARES OF TOTAL $" << stock_volume*stock_price;
                            cout << endl;

                            
                            detailsof_transaction(event, stock_symbol, maximum_amount, stock_volume,stock_price);
                            toInsert(stock_symbol, stock_volume, stock_price,stock_time);
                            
                            
                        }
                    }
                    file_check = 1;


                    
                }
                
            }
            if (file_check == 0)
            {
                cout << "\n THE COMPANY SYMBOL YOU ARE ENTEREING CANNOT BE FOUND\nHENCE, TRANSACTION FAILED!";
            }
            cash_file.close();
        }


        void sell_share()
        {
            char event = '4';
            string company_symbol;
            double evaluation_sold;
            string stock_symbol;
            string stock_time;
            double stock_price;
            double stock_volume = 0;
            double minimum_volume = 0;
            double minimum_amount;
            double total_valuation;
            double stock_total_valuation;
            char choice;
            int file_check = 0;
            double balance = 0;


            ifstream cash_file("balance.txt");
            if (cash_file.is_open() == false)
            {
                balance = 10000;
            }
            else
            {
                cash_file >> balance;
            }


            cout << "PLEASE ENTER THE COMPANY SYMBOL YOU WISH TO SELL THE SHARE FOR: " << endl;
            cin >> company_symbol;
            ifstream data;
            int read_file = rand() % 2;
            if (read_file == 0)
            {
                data.open("Result_1.txt");
            }
            if (read_file == 1)
            {
                data.open("Result_2.txt");
            }

            for (int stock_list = 0; stock_list < 50; stock_list++)
            {
                data >> stock_symbol >> stock_price >> stock_time;
                if (company_symbol == stock_symbol)
                {
                    cout << "ENTER THE NUMBER OF SHARES YOU WISH TO SELL FOR THE COMPANY: ";
                    cin >> stock_volume;

                    
                    

                    
                        cout << "ENTER THE MINIMUM AMOUNT WILLING TO PAY: ";
                        cin >> minimum_amount;

                       
                        
                        balance -= stock_price * stock_volume;
                        
                        cout << "YOU HAVE SOLD SHARES OF TOTAL: $" << stock_volume*stock_price;
                        cout << endl;

                        
                        detailsof_transaction(event, stock_symbol, minimum_amount, stock_volume,stock_price);
                        evaluation_sold = updatelist(stock_symbol, stock_volume, stock_time,stock_price);
                        
                            
                        ifstream cash_file("balance_history.txt");
                        cash_file >> balance;

                        balance = balance + evaluation_sold;

                        ofstream balance_history;
                        balance_history.open("balance_history.txt");

                        balance_history << balance;


                    
                    file_check = 1;


                    
                }
                
            }
            if (file_check == 0)
            {
                cout << "\n THE COMPANY SYMBOL YOU ARE ENTEREING CANNOT BE FOUND\nHENCE, TRANSACTION FAILED!";
            }

        }

        void detailsof_transaction(char event, string stock_symbol, double maximum_amount, double stock_volume,double stock_price)
        {
            string bs;
            time_t seconds;
            seconds = time(NULL);
            tm * timeinfo;
            timeinfo = localtime(&seconds);

            if (event == '3' )
            {
                bs = "BUY";
            } 
            else
            {
                bs = "SELL";
            }

            ofstream stock_transaction;
            stock_transaction.open("stock_transaction_history.txt" , ios::app);
            stock_transaction << bs << " " << stock_symbol << " " << maximum_amount << " $" << stock_price << " $" << stock_volume*stock_price << " " << asctime(timeinfo);
            stock_transaction.close();
        }
        void PrintTableValues(string line)
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
        void transaction_history()
        {
            string myText;
            ifstream MyReadFile("stock_transaction_history.txt");
            cout << "EVENT OF TRANSACTION " << setw(25) << "COMPANY SYMBOL" << setw(25) << "VOLUME OF SHARES" << setw(25) << "COST PER SHARE" << setw(25) << "TOTAL VALUATION" << setw(25) << "TIME OF TRANSACTION" << endl;
            while (getline (MyReadFile, myText)) 
            {
                PrintTableValues(myText);
            }
        }

        void graph_portfolio_value()
        {
            string r_command = "RScript \"/Users/parrthhkharkar/Desktop/FinalProject_Parth Kharkar/portfolio_graph.R";
            system(r_command.c_str());
        }

};