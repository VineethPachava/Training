#include "include/sensor.h"

int Sensor::count = 0;
Sensor::Sensor():m_name(sensor_name){
    m_id = count;
    count++;
}
Sensor::Sensor(const std::string& name):m_name(name){
    m_id = count;
    count++;
}
Sensor::~Sensor(){
    count--;
}

void Sensor::print_raw(){
    std::cout<<m_name<<"\n";
    std::cout<<m_id<<"\n";
}