#ifndef AED_PROJECT2_AIRLINE_H
#define AED_PROJECT2_AIRLINE_H


#include <string>
using namespace std;

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
