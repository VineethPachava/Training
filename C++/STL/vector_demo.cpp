#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v1(100);
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    int sum = 0;
    for(int i=0; i<v1.size();i++)    //Size gives size of object
        sum+=v1.at(i);                    //at "?"

    for (auto x:v1)                     //c++
        sum+=x;
    
    std::vector<int>::iterator iter;
    for(iter=v1.begin();iter!=v1.end();++iter){
        std::cout <<*iter << "\n";
    }

    return 0;
}