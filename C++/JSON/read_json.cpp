#include<iostream>
#include<fstream>
#include  "json.hpp"
using nlohmann::json;

int main(){
    std::ifstream fin("weather.json");
    json j_complete = json::parse(fin);

    for(auto entry : j_complete){
        std::cout<<entry.value("temperature",0)<<"\n";
    }

}