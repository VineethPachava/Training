#ifndef _ACCELEROMETER_H
#define _ACCELEROMETER_H

#include <vector>
#include<iostream>
#include<math.h>
#include "sensor.h"
#include "magnetometer.h"

#define G 9.81
#define PI 3.14159265358979323846 
namespace sensor{
class Magnetometer;

class Accelerometer:public Sensor {
    double acc_x;
    double acc_y;
    double acc_z;   
    
    public:
    Accelerometer();
    Accelerometer(double x, double y, double z);
    ~Accelerometer();


    std::vector<double>linear_acceleration(double gyro_yaw, double gyro_pitch, double gyro_roll);

/* Prints all the accelerometer data. */
    virtual void print_raw();

/* Using the accelerometer data it calcualtes the pitch. */
    double pitch();
    
    /* Using Accelerometer data we are calculating the roll */
    double roll();

    friend std::vector<double>RollPitchYaw(Accelerometer&, Magnetometer&);            
};
}
#endif
