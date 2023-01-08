#ifndef AED_PROJECT2_AIRLINE_H
#define AED_PROJECT2_AIRLINE_H


#include <string>
using namespace std;

//! Airline class
/*!
   A class that contains everthing about an airline, the code, name, callsign and country.
 */
class Airline {
    public:
        Airline();
        Airline(string  code, string  name, string  callsign, string  country);
        string getCode();
        string getName();
        string getCallSign();
        string getCountry();

    private:
        string code_;
        string name_;
        string callsign_;
        string country_;
};


#endif
