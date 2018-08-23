#include <iostream>
using namespace std;

class Complex{
    double m_real;
    double m_imaginary;

    public :
    Complex():m_real(0.0), m_imaginary(0.0){}
    Complex(double real, double imag):m_real(real), m_imaginary(imag){}
    Complex(const Complex& ref):m_real(ref.m_real), m_imaginary(ref.m_imaginary){}
    void display(){
        cout << m_real << m_imaginary<< endl;
    }
    Complex operator+(const Complex ref){
        double treal = m_real + ref.m_real;
        double timag = m_imaginary + ref.m_imaginary;
        return Complex(treal,timag);
    }
    int operator ==(const Complex ref){
        if (m_real == ref.m_real && m_imaginary == ref.m_imaginary ){
            return true;
        }
        else{
            return false;
        }
    }
    friend ostream& operator<<(ostream& ,const  Complex&);
};

ostream& operator<<(ostream& s_out, const Complex& y){
    s_out <<y.m_real<<"+i"<<y.m_imaginary<<endl;
    return s_out;
}

int main()
{
    Complex c1(2.0,3.0);
    Complex c2(1.2,5.6);
    Complex c4(1.2,5.6);
    Complex c5;
    Complex c3;
    c3 = c1 + c2;
    cout<<c1;
    c3.display();
    c5.display();
    if(c2 == c4){
        printf("Same\n");
    }
}
