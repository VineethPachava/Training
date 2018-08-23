#include "include/magnetometer.h"

namespace sensor{
Magnetometer::Magnetometer():mag_x(0.0),mag_y(0.0),mag_z(0.0){}
Magnetometer::Magnetometer(double x,double y,double z):mag_x(x),mag_y(y),mag_z(z){}
Magnetometer::~Magnetometer(){}


void Magnetometer::print_raw(){
        std::cout<<"Magnetic X :"<<mag_x<<";";
        std::cout<<"Magnetic Y :"<<mag_y<<";";
        std::cout<<"Magnetic Z :"<<mag_z<<"\n";
    }
}