#include <iostream>
#include <math.h>
using namespace std;
class Polygon
{
  int nSides;
  public:
  Polygon(int n):nSides(n)
  {
    
  }
  virtual void display()
  {
    std::cout << "No.of sides i am main: " << nSides << "\n";
  }
  virtual double area()
  {
    //do-
    return 0.0;
  }
  virtual double perimeter()
  {
    //do-nothingKNNN
    return 0.0;
  }
};
class Triangle:public Polygon
{
  double a;
  double b;
  double c;
  public:
  Triangle(int x,int y,int z):Polygon(3),a(x),b(y),c(z)
  {
    
  }
  virtual void display()
  {    
    std::cout << "Triangle i am derived-->" << a << "," << b << "," << c << "\n";
  }
  double area()
  {
    double  s=(a+b+c)/2;
    return sqrt( s*(s-a)*(s-b)*(s-c));    
  }
  double perimeter()
  {
    return a+b+c;
  }
};
class Rectangle:public Polygon
{
  int l;
  int b;
  public:
  Rectangle(int x,int y):Polygon(4),l(x),b(y)
  {
    
  }
  void display()
  {
    std::cout << "l=" << l << ",b=" << b << "\n"; 
  }
  double area()
  {
    return l*b;
  }  
  double perimeter()
  {
    return 2*(l+b);
  }
};
int main() {

  Polygon *ptr1;
  Triangle *ptr2;

  ptr1=new Triangle(3.0,4.0,5.0);
  // ptr2=new Rectangle(10.0,20.0);
  // ptr3=new Polygon(10);
  
  ptr1->display();
  // ptr2->display();
  
  // std::cout << ptr2->area() << "\n";
  // std::cout << ptr2->perimeter() << "\n";
  
  delete ptr1;
  // delete ptr2;
  return 0;
}