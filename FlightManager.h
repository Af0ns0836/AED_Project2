#ifndef AED_PROJECT2_FLIGHTMANAGER_H
#define AED_PROJECT2_FLIGHTMANAGER_H

#include <list>
#include "Airport.h"
#include "Flight.h"
#include "Airline.h"

class FlightManager {
    public:
        FlightManager();
        void menu();
        void readFiles();
        void readAirports();
        void readAirlines();
        void readFlights();

    private:
        list<Airport*> airports_;
        list<Flight*> flights_;
        list<Airline*> airlines_;
};


#endif
