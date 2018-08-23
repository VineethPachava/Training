#include <iostream>
#include <typeinfo>
using namespace std;


class A {
 public:
  void f1();
  void f2();
  void f3();
};

class C:public A
{
 public:
  void f1();  
};


int main(){
int x =0;
float y;
const int max=10;

A b1;
const A *pb=&b1; 
// const C &rb= b1;
std::cout << typeid(x).name() << "\n";
std::cout << typeid(y).name() << "\n";
std::cout << typeid(b1).name() << "\n";
std::cout << typeid(pb).name() << "\n";
std::cout << typeid(*pb).name() << "\n";
// std::cout << typeid(rb).name() << "\n";
}