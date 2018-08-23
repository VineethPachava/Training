#include "include/gps.h"

namespace sensor{
/*  Function to parse the data  */
double GPS::parsing(std::string& longit){
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

/* Default constructor */
GPS::GPS():m_latitude(0.0),m_longitude(0.0){}
/* Parsing the lattitude and longitude to double from string format in the constructor  */
GPS::GPS (std::string latitude, std::string longitude){
    m_latitude = parsing(latitude);
    m_longitude = parsing(longitude);
}
    /* Destructor */
GPS::~GPS(){}
/* "-" operator is overlaoded to calculate the distance between two GPS location using haversine formula */
double GPS::operator-(GPS& ref){
    // found haversine logic from stack overflow
    double lat1 = m_latitude;
    double long1 = m_longitude;
    double lat2 = ref.m_latitude;
    double long2 = ref.m_longitude;
    double dlong = (long2 - long1) * PI/180;
    double dlat = (lat2 - lat1) * PI/180;
    double a = pow(sin(dlat/2.0), 2) + cos(lat1*PI/180) * cos(lat2*PI/180) * pow(sin(dlong/2.0), 2);
    double c = 2*atan2(sqrt(a), sqrt(1-a));
    double d = 6367 * c;
    return d;
    }
void GPS::print_raw(){
    std::cout<<"Latitude: "<<m_latitude<<" ";
    std::cout<<"Longitude"<<m_longitude<<"\n";
}
}