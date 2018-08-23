#include<iostream>
#include<fstream>
#include "json.hpp"     
#include <math.h>
#include <vector>
#include<typeinfo>
#include<memory>
#include<string>

using nlohmann::json;
#define G 9.81
#define PI 3.14159265358979323846 

class Magnetometer; //forward decleration

class Sensor {
    static int count; 
    std::string sensor_name = "not_defined";  
    protected:
    std::string m_name;
    int m_id;
    
    public:
    explicit Sensor():m_name(sensor_name){
        m_id = count;
        count++;
    }
    explicit Sensor(std::string& name):m_name(name){
        m_id = count;
        count++;
    }
    ~Sensor(){
        count--;
    }

    virtual void print_raw(){
        std::cout<<m_name<<"\n";
        std::cout<<m_id<<"\n";
    }
};
int Sensor::count = 1;
class Accelerometer:public Sensor {
    double acc_x;
    double acc_y;
    double acc_z;   
    
    public:
    Accelerometer():acc_x(0.0),acc_y(0.0),acc_z(0.0){
        m_name = "Accelerometer";
    }
    Accelerometer(double x, double y, double z):acc_x(x),acc_y(y),acc_z(z){
        // std::cout<<acc_x<<acc_y<<acc_z<<"\n";
    }
    ~Accelerometer(){}
    friend std::vector<double>RollPitchYaw(Accelerometer&, Magnetometer&);

    std::vector<double>linear_acceleration(double gyro_yaw, double gyro_pitch, double gyro_roll){
        double g_x;
        double g_y;
        double g_z;

        // g_x = (-cos(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) - sin(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
        // g_y = (-sin(gyro_yaw*PI/180)*sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180) + cos(gyro_yaw*PI/180)*cos(gyro_roll*PI/180))*G;
        // g_z = (sin(gyro_pitch*PI/180)*sin(gyro_roll*PI/180))*G;
        
        // g_x = sin(beta)*G;
        // g_y = 0.5*sin(beta-gamma) - 0.5*sin(beta-gamma);
        // g_z = 0.5*cos(beta-gamma) + 0.5*cos(beta-gamma);

        
        std::vector<double> v;
        v.push_back(g_x);
        v.push_back(g_y);
        v.push_back(g_z);

        return v;
    }
/* Prints all the accelerometer data. */
    virtual void print_raw(){
        std::cout<<acc_x<<"\n";
        std::cout<<acc_y<<"\n";
        std::cout<<acc_z<<"\n";
    }
/* Using the accelerometer data it calcualtes the pitch. */
    double pitch(){
        double pitch;
        // double yaw;
        pitch =  atan2(acc_x,sqrt((acc_y*acc_y + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return pitch;
    }
    /* Using Accelerometer data we are calculating the roll */
    double roll(){
        double roll;
        // double yaw;
        roll =  atan2(acc_y,sqrt((acc_x*acc_x + acc_z*acc_z)))*180/PI;
        // std::cout<<yaw<<"\n";
        return roll;
    }


            
};

class Magnetometer: public Sensor {
    double mag_x;
    double mag_y;
    double mag_z;
    public:
    Magnetometer():mag_x(0.0),mag_y(0.0),mag_z(0.0){}
    Magnetometer(double x,double y,double z):mag_x(x),mag_y(y),mag_z(z){}
    ~Magnetometer(){}
    friend std::vector<double>RollPitchYaw(Accelerometer&,Magnetometer&);

    virtual void print_raw(){
        std::cout<<mag_x<<"\n";
        std::cout<<mag_y<<"\n";
        std::cout<<mag_z<<"\n";
    }
};

/* Class handling the sensor GPS */
class GPS:public Sensor {
    double m_latitude;
    double m_longitude;
/*  Function to parse the data  */
    double parsing(std::string& longit){
        //thanks to sri krishna for the parsing code
        std::string s = longit;
        std::string delimiter1 = "°";
        std::string delimiter2 = "‘";
        std::string delimiter3 = "‘‘";
        size_t pos1,pos2,pos3 = 0;
        pos1= s.find(delimiter1);
        pos2= s.find(delimiter2);
        pos3= s.find(delimiter3);
        // std::string token;
        std::string token1 = s.substr(0,pos1); 
        std::string token2 = s.substr(pos1+delimiter1.length(),pos2-delimiter2.length()-1);
        std::string token3 = s.substr(pos2+delimiter2.length(),pos3-delimiter3.length()-4);
        double rtn=stod(token1)+stod(token2)/60.0+stod(token3)/3600.0;

        return rtn ;
    }

    public:
    /* Default constructor */
    GPS():m_latitude(0.0),m_longitude(0.0){}
    /* Parsing the lattitude and longitude to double from string format in the constructor  */
    GPS (std::string latitude, std::string longitude){
        m_latitude = parsing(latitude);
        m_longitude = parsing(longitude);
    }
    /* Destructor */
    ~GPS(){}
/* "-" operator is overlaoded to calculate the distance between two GPS location using haversine formula */
    double operator-(GPS& ref){
        // found haversine logic from stack overflow
        double lat1 = m_latitude;
        double long1 = m_longitude;
        double lat2 = ref.m_latitude;
        double long2 = ref.m_longitude;
        double dlong = (long2 - long1) * PI/180;
        double dlat = (lat2 - lat1) * PI/180;
        double a = pow(sin(dlat/2.0), 2) + cos(lat1*PI/180) * cos(lat2*PI/180) * pow(sin(dlong/2.0), 2);
        double c = 2 * atan2(sqrt(a), sqrt(1-a));
        double d = 6367 * c;
        return d;
        }
    virtual void print(){
        std::cout<<m_latitude<<"\n";
        std::cout<<m_longitude<<"\n";
    }
};

/* Friend funtion for both magnetometer and accelerometer class to calculate Roll Pitch Yaw */
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
    // std::cout<<pitch<<"\n"<<roll<<"\n"<<yaw<<"\n";
    orient.push_back(roll);
    orient.push_back(pitch);
    orient.push_back(yaw);
    return orient;

}

int main(){
    // Accelerometer obj_acc(1.7386, 2.5901, 9.5825);
    // std::vector <double> l_acc = obj_acc.linear_acceleration(-45.12,19.72,10.76);
    // std::vector<double>::iterator iter;
    // Magnetometer obj_mag (-31.16,23.09,-12.73);
    // std::vector<double> rpy = RollPitchYaw(obj_acc,obj_mag);
    // for(iter=l_acc.begin();iter!=l_acc.end();++iter){
    //     std::cout <<*iter << "\n";
    // }

    // std::vector <double> orient = obj_acc.RollPitchYaw();
    // std::cout<<sin(90*PI/180)<<"\n";

    std::ifstream fin("sensor.json");
    json j_complete = json::parse(fin);
    auto entry = j_complete;
    
    std::vector<std::shared_ptr<Sensor>> acc_ptr;
    std::vector<std::shared_ptr<Sensor>> mag_ptr;

// using vector of objects for gps pointer
    std::vector<GPS> gps_ptr;  

    

    for(auto entry : j_complete){
        std::shared_ptr<Sensor> data_ptr_acc(new Accelerometer(entry["ACCELEROMETER_X"].get<double>(),
                                     entry["ACCELEROMETER_Y"].get<double>(),
                                     entry["ACCELEROMETER_Z"].get<double>()));
        std::shared_ptr<Sensor> data_ptr_magnet(new Magnetometer(entry["MAGNETIC FIELD X (μT)"].get<double>(),
                                     entry["MAGNETIC FIELD_Y"].get<double>(),
                                     entry["MAGNETIC FIELD_Z"].get<double>()));
        // std::shared_ptr<Sensor> data_ptr_gps(new GPS(entry["LOCATION_Latitude"].get<std::string>(),
        //                              entry["LOCATION_Longitude"].get<std::string>()));



        acc_ptr.push_back(data_ptr_acc);
        mag_ptr.push_back(data_ptr_magnet);
    
        // gps_ptr.push_back(data_ptr_gps);
        gps_ptr.push_back(GPS(entry["LOCATION_Latitude"].get<std::string>(),
                                     entry["LOCATION_Longitude"].get<std::string>()));

        // std::cout<<typeid(acc_ptr).name()<<"\n";
        // std::cout<<""<<"\n";
        }

        ((acc_ptr.at(0))->print_raw());
        RollPitchYaw(static_cast<Accelerometer&>(*(acc_ptr.at(4))),
                                static_cast<Magnetometer&>(*(mag_ptr.at(4))));

        std::vector<std::shared_ptr<Sensor>>::iterator iter_1;
        for(iter_1=acc_ptr.begin();iter_1!=acc_ptr.end();++iter_1){
            (*iter_1)->print_raw(); 
        }
        
        double x_distance = 0;
        for(auto it = gps_ptr.begin(); it!=gps_ptr.end()-1; ++it){
            double dx = 0 ;
            dx = *(++it)-*it;
            x_distance = x_distance + dx;
        }
        std::cout<<x_distance<<"\n";

    // acc_ptr.clear();
    // mag_ptr.clear();
    // gps_ptr.clear();
    // acc_ptr.shrink_to_fit();
    // mag_ptr.shrink_to_fit();
    // gps_ptr.shrink_to_fit();
}   