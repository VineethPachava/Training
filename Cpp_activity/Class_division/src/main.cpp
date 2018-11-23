#include<fstream>
#include<iostream>
#include "include/sensor.h"
#include "include/accelerometer.h"
#include "include/magnetometer.h"
#include "include/functions.h"
#include "include/gps.h"
#include "include/json.hpp"     


using nlohmann::json;
#define G 9.81
#define PI 3.14159265358979323846 

int main(){
    std::ifstream fin("sensor.json");
    json j_complete = json::parse(fin);
    auto entry = j_complete;

/* Testing Sensor Class */
    std::cout<<"Tesing the default constructors"<<"\n";
    Sensor test_sensor("Testsensor");
    test_sensor.print_raw();
    std::cout<<"==================================="<<"\n";
/* Testing all the default constructors  */
    std::cout<<"Tesing the default constructors"<<"\n";
    Sensor def_obj_sen;
    def_obj_sen.print_raw();
    std::cout<<"==================================="<<"\n";
    sensor::Accelerometer def_obj_acc;
    def_obj_acc.print_raw();
    std::cout<<"==================================="<<"\n";    
    sensor::Magnetometer def_obj_mag;
    def_obj_mag.print_raw();
    std::cout<<"==================================="<<"\n";
    sensor::GPS def_obj_gps;
    def_obj_gps.print_raw();
    std::cout<<"==================================="<<"\n";



/* Creating a vector of smart pointers pointing to the objects of accelerometer and magnetometer */
    std::vector<std::shared_ptr<Sensor>> acc_ptr;
    std::vector<std::shared_ptr<Sensor>> mag_ptr;

/*  Creating vector of objects for gps pointer */
    std::vector<sensor::GPS> gps_ptr;  

    

    for(auto entry : j_complete){
        std::shared_ptr<Sensor> data_ptr_acc(new sensor::Accelerometer(entry["ACCELEROMETER_X"].get<double>(),
                                     entry["ACCELEROMETER_Y"].get<double>(),
                                     entry["ACCELEROMETER_Z"].get<double>()));
        std::shared_ptr<Sensor> data_ptr_magnet(new sensor::Magnetometer(entry["MAGNETIC FIELD X (μT)"].get<double>(),
                                     entry["MAGNETIC FIELD_Y"].get<double>(),
                                     entry["MAGNETIC FIELD_Z"].get<double>()));

        acc_ptr.push_back(data_ptr_acc);
        mag_ptr.push_back(data_ptr_magnet);
    
        gps_ptr.push_back(sensor::GPS(entry["LOCATION_Latitude"].get<std::string>(),
                                     entry["LOCATION_Longitude"].get<std::string>()));

        }
        
        std::cout<<"Printing first five acceleration data points"<<"\n";
        for(int i=0; i<5 ; i++){
        ((acc_ptr.at(i))->print_raw());
        }

        /* printing first five parsed logitude and latitude values */
        std::cout<<"==================================="<<"\n";
        std::cout<<"Printing first five GPS data points"<<"\n";
        for(int i=0; i<5 ; i++){
        ((gps_ptr.at(i)).print_raw());
        }
        /* Calculating the roll pitch yaw */
         RollPitchYaw(static_cast<sensor::Accelerometer&>(*(acc_ptr.at(4))),
                                static_cast<sensor::Magnetometer&>(*(mag_ptr.at(4))));

        /* Printing Linear velocity */
        // std::vector <double> l_acc = obj_acc.linear_acceleration(-45.12,19.72,10.76);
        // std::vector<double>::iterator iter;
        // for(iter=l_acc.begin();iter!=l_acc.end();++iter){
        //     std::cout <<*iter << "\n";
        // }

        /* Calculating the distance from the gps data */
        double x_distance = 0;
        for(auto it = gps_ptr.begin(); it!=gps_ptr.end()-1; ++it){
            double dx = 0 ;
            dx = *(++it)-*it;
            x_distance = x_distance + dx;
        }
        std::cout<<"Distance Moved :"<<x_distance<<"\n";

}   