#include <iostream>
using namespace std;

template<typename T>
T sum(T x,T y)
{
    T z;
    z=x+y;
    return z;
}


int main(){
int a=10,b=20;
float x=2.3f,y=5.6f;
double p=2.3,q=5.6;
cout << sum(a,b) << endl;       //T:int
}
