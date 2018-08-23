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