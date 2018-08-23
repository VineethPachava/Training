
#ifndef _SENSOR_H
#define _SENSOR_H

#include<string>
#include<iostream>

class Sensor { 
    std::string sensor_name = "not_defined";  
    protected:
    std::string m_name;
    int m_id;
    static int count;

    
    public:
    explicit Sensor();
    explicit Sensor(const std::string& name);
    ~Sensor();

    virtual void print_raw();
};
#endif