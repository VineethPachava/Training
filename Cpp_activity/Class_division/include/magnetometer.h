#ifndef _MAGNETOMETER_H
#define _MAGNETOMETER_H


#include<iostream>
#include <vector>
#include "accelerometer.h"
#include "sensor.h"

namespace sensor{
class Accelerometer;

class Magnetometer: public Sensor {
    double mag_x;
    double mag_y;
    double mag_z;
    public:
    Magnetometer();
    Magnetometer(double x,double y,double z);
    ~Magnetometer();

    /* Friend Function to calulate the ROLL PITCH YAW */
    friend std::vector<double>RollPitchYaw(Accelerometer& ,Magnetometer&);

/* Prints the magnetometer values */
    virtual void print_raw();
};
}
#endif