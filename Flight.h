#ifndef AED_PROJECT2_FLIGHT_H
#define AED_PROJECT2_FLIGHT_H


#include "Airport.h"
#include "Airline.h"
#include <string>
using namespace std;

class Flight {
    public:
        Flight();
        Flight(Airport* source, Airport* target, Airline* airline);
        Airport * getSource();
        Airport* getTarget();
        Airline* getAirline();

    private:
        Airport* source_;
        Airport* target_;
        Airline* airline_;
};


#endif
