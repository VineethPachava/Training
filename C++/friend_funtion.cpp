#include <iostream>

class Sample
{
  int x;
  int y;
  public:
  Sample(int p,int q):x(p),y(q)
  {

  }
  friend void setx(Sample*,int);
  friend void sety(Sample*,int);
  friend void printxy(Sample&);
};
void setx(Sample* ptr,int w)
{
  ptr->x=w;
}
void sety(Sample* ptr,int q)
{
  ptr->y=q;
}
void printxy(Sample& ref)
{
  std::cout << ref.x << "," << ref.y << "\n";
}
int main()
{
  Sample s1(10,20);
  setx(&s1,15);
  sety(&s1,20);
  printxy(s1);
  return 0;
}