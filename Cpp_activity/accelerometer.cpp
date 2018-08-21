#include<iostream>
#include<fstream>
#include  "json.hpp"
#include <math.h>
#include <vector>

using nlohmann::json;
#define G 9.81
#define PI 3.14159265358979323846 

class magnetometer; //forward decleration

class accelerometer {
    double acc_x;
    double acc_y;
    double acc_z;   
    
    public:
    accelerometer():acc_x(0.0),acc_y(0.0),acc_z(0.0){}
    accelerometer(double x, double y, double z):acc_x(x),acc_y(y),acc_z(z){
        // std::cout<<acc_x<<acc_y<<acc_z<<"\n";
    }
    ~accelerometer(){}
    friend std::vector<double>orientation(accelerometer&, magnetometer&);

    std::vector<double>linear_acceleration(double gyro_yaw, double gyro_pitch, double gyro_roll){
        double g_x;
        double g_y;
        double g_z;

        g_x = (-cos(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) - sin(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
        g_y = (-sin(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) + cos(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
        g_z = (sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180))*G;
        std::vector<double> v;
        v.push_back(g_x);
        v.push_back(g_y);
        v.push_back(g_z);

        return v;
    }

    void print_acceleration(){
        std::cout<<acc_x<<"\n";
        std::cout<<acc_y<<"\n";
        std::cout<<acc_z<<"\n";
    }

    void mangnitude_linear_acceleration(){
        

    }

    double pitch(){
        double pitch;
        // double yaw;
        pitch =  atan2(acc_x,sqrt((acc_y*acc_y + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return pitch;
    }
        double roll(){
        double roll;
        // double yaw;
        roll =  atan2(acc_y,sqrt((acc_x*acc_x + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return roll;
    }


            
};

class magnetometer{
    double mag_x;
    double mag_y;
    double mag_z;
    public:
    magnetometer():mag_x(0.0),mag_y(0.0),mag_z(0.0){}
    magnetometer(double x,double y,double z):mag_x(x),mag_y(y),mag_z(z){}
    ~magnetometer(){}
    friend std::vector<double>orientation(accelerometer&,magnetometer&);

    void print_acceleration(){
        std::cout<<mag_x<<"\n";
        std::cout<<mag_y<<"\n";
        std::cout<<mag_z<<"\n";
    }
};

std::vector<double>orientation(accelerometer& obj_acc, magnetometer& obj_mag){
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
    std::cout<<pitch<<"\n"<<roll<<"\n"<<yaw<<"\n";
    orient.push_back(roll);
    orient.push_back(pitch);
    orient.push_back(yaw);
    return orient;

}


int main(){
    accelerometer obj_acc(1.7386, 2.5901, 9.5825);
    std::vector <double> l_acc = obj_acc.linear_acceleration(-45.12,19.72,10.76);
    std::vector<double>::iterator iter;
    magnetometer obj_mag (-31.16,23.09,-12.73);
    std::vector<double> rpy = orientation(obj_acc,obj_mag);
    // for(iter=l_acc.begin();iter!=l_acc.end();++iter){
    //     std::cout <<*iter << "\n";
    // }

    // std::vector <double> orient = obj_acc.orientation();
    // std::cout<<sin(90*PI/180)<<"\n";




    std::ifstream fin("sensor.json");
    json j_complete = json::parse(fin);
    auto entry = j_complete;
    for(auto entry : j_complete){
        std::cout<<entry["ACCELEROMETER_X"].get<double>()<<"\n";
    }
}