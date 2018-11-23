#ifndef _GPS_H
#define _GPS_H

#include<iostream>     
#include <vector>
#include<string>
#include "sensor.h"
#include<math.h>

#define G 9.81
#define PI 3.14159265358979323846 
namespace sensor{
class GPS:public Sensor {
    double m_latitude;
    double m_longitude;
/*  Function to parse the data  */
    double parsing(std::string& longit);

    /* Default constructor */
    public:

    GPS();

    /* Parsing the lattitude and longitude to double from string format in the constructor  */
    GPS (std::string latitude, std::string longitude);

    /* Destructor GPS*/
    ~GPS();

/* "-" operator is overlaoded to calculate the distance between two GPS location using haversine formula */
    double operator-(GPS& ref);

    /* Prints the values of magnetometer */
    virtual void print_raw();
};
}
#endif