#include <iostream>
#include <map>

int main(){
    std::map<int,std::string> names;
    names[101] ="My name";
    names[102] = "I am noob";
    names[103] = "lol";
    names.insert(std::pair<int,std::string>(104,"sri....."));

    for(auto entry:names)
        std::cout  << entry.first <<","<<entry.second<<"\n";
    
    for (auto iter = names.begin();iter!=names.end();iter++)
        std::cout<<iter->first<<","<<iter->second<<"\n";
    auto result = names.find(102);
    std::cout<<result->first<<","<<result->second<<"\n";
    return 0;

}