#include <iostream>
using namespace std;

class Account
{
    int id;
    string name;
    double balance;
    public:

    void open(int,std::string,double);
    void credit(double);
    void debit(double);
    void display();
    double getBalance();
};

void Account::open(int x,string str,double y)
{
    id=x;
    name=str;
    balance=y;
}
void Account::credit(double amount)
{
    balance+=amount;
}
void Account::debit(double amount)
{
    balance-=amount;
}
double Account::getBalance()
{
    return balance;
};