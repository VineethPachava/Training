#include<iostream>
class Host
{
  int x;
  int y;
  public:
  Host(int p,int q):x(p),y(q)
  {

  }
  friend class Guest;
};
class Guest
{

  public:

  static void setx(Host* ptr,int p)
  {
    ptr->x=p;
  }
  static void sety(Host* ptr,int q)
  {
    ptr->y=q;
  }
  static void printxy(Host& ref)
  {
    std::cout << ref.x << "," << ref.y << "\n";
  }
};
int main()
{
  Host h1(10,20);
  Guest obj2;
  Guest::setx(&h1,15);
  Guest::sety(&h1,25);
  Guest::printxy(h1);
}