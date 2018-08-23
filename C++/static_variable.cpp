#include<iostream>
class Sample
{
  int x;
  int y;
  public:
  static int k;
  Sample(int p,int q):x(p),y(q)
  { 
  }
  void printxy()
  {
    std::cout << "x=" << x << "y=" << y << "\n";
  }
};

int Sample::k=0;

int main() 
{
  Sample s1(10,20);
  Sample s2(11,21);
  Sample s3(12,22);
  s1.k=100;
  s2.k=200;
  std::cout << s1.k << "," << s2.k << "," << s3.k << "\n";
  std::cout << Sample::k << "\n";
  return 0;
}