#include <iostream>

#define PI 3.14
#define SQUARE(x) (x)*(x)
using namespace std;
int a =10;
int b;
float p =2.3f;
float q;
const int max= 100;

int main(){
    int x=10;
    int y=20;
    int z;
    z =x+y;
    //print Z
    double rad=7.0,area;
    area= PI * SQUARE(2);\
    int *parr,len=10;
    parr=new int[len];
    for(int i=0;i<len;i++)
        parr[i]=rand()%100;
    for(int i=0;i<len;i++)
        cout << parr[i] << "\n";
    // delete[] parr;
 

}