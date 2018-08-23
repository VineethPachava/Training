#include "json.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

using json =nlohmann::json;


int main(){
json encoder;
encoder["temperature"]=24;
encoder["humidity"] = 72;
encoder["pressure"] = 20;
std::cout<<encoder.dump()<<"\n";


auto text =R"(
    "temperature":24,
    "humidity":72,
    "pressure":560
})";
char str ;
std::stringstream ss ;
json j_complete = json::parse(ss);
// j_complete =
  std::ifstream fin("simple.json");
json j_complete = json::parse(fin);

}