#include <iostream>
#include<cstring>
using namespace std;


class MyString
{
    char* m_buf;
    int m_len;
  public:
    //default ctor -- optional, can set m_buf to NULL and m_len to zero
    MyString(const char* ps)
    {
        m_len=strlen(ps);
        m_buf=new char[m_len+1];
        strcpy(m_buf,ps);
    }
    MyString(const MyString& ref)
    {
        m_len=ref.m_len;
        m_buf=new char[m_len+1];
        strcpy(m_buf,ref.m_buf);
    }
    ~MyString()
    {
        delete[] m_buf;
    }
    void prints() const
    {
        cout << m_buf << "\n";
    }
    int length() const
    {
        return m_len;
    }
};

int main(){
    
}
