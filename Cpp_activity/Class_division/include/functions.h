#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H
#include "accelerometer.h"
#include "magnetometer.h"
#include <math.h>
#include<vector>
#include<iostream>
namespace sensor{
std::vector<double>RollPitchYaw(Accelerometer& obj_acc, Magnetometer& obj_mag);
}
#endif