#include "include/accelerometer.h"
namespace sensor{


    Accelerometer::Accelerometer():acc_x(0.0),acc_y(0.0),acc_z(0.0){
        m_name = "Accelerometer";
    }
    Accelerometer::Accelerometer(double x, double y, double z):acc_x(x),acc_y(y),acc_z(z){
        // std::cout<<acc_x<<acc_y<<acc_z<<"\n";
    }
    Accelerometer::~Accelerometer(){}
    

    // std::vector<double>Accelerometer::linear_acceleration(double gyro_yaw, double gyro_pitch, double gyro_roll){
    //     double g_x;
    //     double g_y;
    //     double g_z;

    //     g_x = (-cos(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) - sin(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
    //     g_y = (-sin(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) + cos(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
    //     g_z = (sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180))*G;
        
    //     // g_x = sin(beta)*G;
    //     // g_y = 0.5*sin(beta-gamma) - 0.5*sin(beta-gamma);
    //     // g_z = 0.5*cos(beta-gamma) + 0.5*cos(beta-gamma);

        
    //     std::vector<double> v;
    //     v.push_back(g_x);
    //     v.push_back(g_y);
    //     v.push_back(g_z);

    //     return v;
    // }
/* Prints all the accelerometer data. */
    void Accelerometer::print_raw(){
        std::cout<<"acceleration X :"<<acc_x<<";";
        std::cout<<"acceleration Y :"<<acc_y<<";";
        std::cout<<"acceleration Z :"<<acc_z<<"\n";
    }

/* Using the accelerometer data it calcualtes the pitch. */
    double Accelerometer::pitch(){
        double pitch;
        // double yaw;
        pitch =  atan2(acc_x,sqrt((acc_y*acc_y + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return pitch;
    }

    /* Using Accelerometer data we are calculating the roll */
    double Accelerometer::roll(){
        double roll;
        // double yaw;
        roll =  atan2(acc_y,sqrt((acc_x*acc_x + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return roll;
    } 
}