#include "include/functions.h"

namespace sensor{
std::vector<double>RollPitchYaw(Accelerometer& obj_acc, Magnetometer& obj_mag){
   std::vector<double> orient;
   double pitch;
   double roll;
   double yaw;
   double y_val;
   double x_val;

   pitch = obj_acc.pitch();
   roll = obj_acc.roll();
    x_val = obj_mag.mag_x*cos(pitch) + obj_mag.mag_y*sin(roll)*sin(pitch) + obj_mag.mag_z*cos(roll)*sin(pitch);
    y_val = obj_mag.mag_y * cos(roll) - obj_mag.mag_z * sin(roll);
    yaw = 180 * atan2(-y_val,x_val)/PI;
    std::cout<<"=============================="<<"\n";
    std::cout<<"Printing Pitch Roll Yaw of below values"<<"\n";
    obj_acc.print_raw();
    obj_mag.print_raw();
    std::cout<<"Pitch  Roll  Yaw of above values"<<"\n";
    std::cout<<pitch<<" "<<roll<<" "<<yaw<<"\n";
    std::cout<<"=============================="<<"\n";  
    orient.push_back(roll);
    orient.push_back(pitch);
    orient.push_back(yaw);
    return orient;
}
}